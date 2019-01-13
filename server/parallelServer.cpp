//
// Created by Evyatar on 1/13/2019.
//

#include <iostream>
#include "parallelServer.h"
#include "sockets/sockets.h"
#include "threads/threads.h"
#include "fdbuf.h"
#include <netinet/in.h>

namespace server_side {
    using namespace exceptions;
    using namespace threads;
    using namespace std;

    struct ServerData {
        TCPServer server;
        ClientHandler* clientHandler;
        bool* open;
        int tv_sec; // timeout seconds
    };

    struct ClientData {
        TCPSocket client;
        ClientHandler* handler;
    };

    /**
     * This function handles the client.
     * @param args a ClientData* instance
     */
    void* clientHandler(void* args) {
        ClientData* inData = (ClientData*) args;
        ClientData data(*inData);
        delete inData;

        // create input and output stream
        fdbuf buf(data.client.fd());
        istream is(&buf);
        ostream os(&buf);

        // try handling client, might throw exceptions
        try { inData->handler->handleClient(is, os); }
        catch (const exception& e) { cerr << e.what() << endl; }
        catch (...) { cerr << "error handling client" << endl; }

        try { data.client.close(); }
        catch (const exception& e) { cerr << e.what() << endl; }
    }

    /**
     * This function handles the server.
     * @param args a ServerData* instance
     */
    void* serverHandler(void* args){
        ServerData* inData = (ServerData*) args;
        ServerData data(*inData);
        delete inData;

        // thread pool of the clients
        ThreadPool clientsPool;

        bool firstRun = true;

        // run while is open
        while (data.open) {
            TCPSocket client;
            try {
                client = data.server.accept(); // try accepting
                client.setTimeout(1, 0); // try setting timeout
            }
            catch (const exception& e) {
                cerr << e.what() << endl;
                continue;
            }
            catch (...) {
                try { client.close(); }
                catch (...) {
                    cerr << "error closing client" << endl;
                    continue;
                }
            }

            // try running client
            ClientData* clientData = new ClientData;
            clientData->handler = data.clientHandler;
            clientData->client = client;

            try {
                // create client data
                Thread* t = new Thread(clientHandler, clientData);
                clientsPool.add(t);
            }
            catch (const exception& e) {
                delete clientData;
                cerr << e.what() << endl;
            }
            catch (...) {
                delete clientData;
                try { client.close(); }
                catch (...) { cerr << "error closing client after thread creation." << endl; }
            }

            // set timeout after first run
            if (firstRun) {
                firstRun = false;
                data.server.setTimeout(data.tv_sec);
            }
        }

        // wait for clients to finish
        clientsPool.join();

        // try closing
        try {
            data.server.close();
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }

    bool ParallelServer::open(int port, server_side::ClientHandler *ch) {
        using namespace exceptions;
        using namespace threads;

        try {
            TCPServer server(port);
            server.listen(SOMAXCONN);

            ServerData* data = new ServerData{server};
            data->tv_sec = 1;
            data->clientHandler = ch;
            data->open = &_open;

            try {
                _serverThread = new Thread(serverHandler, data);
            }
            catch (const exception& e) {
                cerr << e.what() << endl;
                delete data;
                server.close();
                return false;
            }
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
            return false;
        }
        catch (...) {
            cerr << "error in server" << endl;
            return false;
        }

        return true;
    }

    bool ParallelServer::isOpen() {
        return _serverThread;
    }

    void ParallelServer::close() {
        _open = false;
        _serverThread->join();
        _serverThread = nullptr;
    }
}