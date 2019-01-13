#ifndef MILESTONE_2_SERIALSERVER_H
#define MILESTONE_2_SERIALSERVER_H

#include "server.h"
#include "clientHandler.h"

namespace server_side {
    class MySerialServer : public server_side::Server {
    private:
        int _sockfd;
        bool _open;

        pthread_t threadId;

    protected:
        /**
         * Accept clients on separate thread.
         * @param handler a client handler
         * @return true if managed to open thread, false otherwise
         */
        virtual bool acceptClients(server_side::ClientHandler* handler);
    public:

        /**
         * Construct a new serial server.
         * @param maxconn the maximal amount of connections allowed.
         */
        MySerialServer() :
                _sockfd(-1), _open(false) { };

        virtual bool open(int port, server_side::ClientHandler* clientHandler);

        virtual void close();

        virtual bool isOpen();

        virtual void wait();

        /**
         * Destructor.
         */
        virtual ~MySerialServer() { close(); }
    };
}

#endif
