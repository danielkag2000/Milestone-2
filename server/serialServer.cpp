#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

#include "serialServer.h"

using namespace server_side;

/**
 * Create a server socket.
 * @param port the port
 * @return a socket file descriptor. if negative then failed opening.
 */
int createServerSocket(int port) {
    int sockfd;

    sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket.");
        return -1;
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

//    // set timeout
//    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))) {
//        // if error
//        perror("ERROR on setting timeout.");
//        close(sockfd);
//        return -1;
//    }

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding.");
        close(sockfd);
        return -1;
    }

    // listen to incoming connections
    if (listen(sockfd, 1) < 0) {
        perror("ERROR on listening.");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

bool MySerialServer::open(int port, ClientHandler* clientHandler) {
#define FINISH\
    _open = false;\
    _sockfd = -1;

    _open = true;

    _sockfd = createServerSocket(port);

    if (_sockfd < 0) {
        FINISH
        return false;
    }

    if (!acceptClients(clientHandler)) {
        FINISH
        ::close(_sockfd);
        return false;
    }

    cout << "finished opening." << endl;
}

bool MySerialServer::isOpen() {
    return _open && _sockfd >= 0;
}

void MySerialServer::close() {
    _open = false;

    ::close(_sockfd);
    _sockfd = -1;

    pthread_join(threadId, nullptr);
}

struct ServerData {
    ClientHandler* clientHandler;

    const bool& open;
    const int& fd;

    int tv_sec;
    int tv_usec;

    ~ServerData() {
        delete clientHandler;
    }
};

void MySerialServer::wait() {
    throw "unsupported operation";
}

#include "fdbuf.h"

/**
 * Handle server in parallel.
 * @param in a ServerData instance
 * @return null
 */
void* parallelHandle(void* in) {
    ServerData* data = (ServerData*) in;

    timeval timeout;
    timeout.tv_sec = data->tv_sec;
    timeout.tv_usec = data->tv_usec;

    while (data->open) {
        int clientfd = accept(data->fd, NULL, 0);

        // set receive timeout
        setsockopt(clientfd, SOL_SOCKET, SO_RCVTIMEO,
                   (char *)&timeout, sizeof(timeout));

        if (clientfd < 0) {
            perror("ERROR accepting client.");
            continue;
        }

        fdbuf buf(clientfd);
        istream is(&buf);
        ostream os(&buf);

//        data->clientHandler->handleClient({clientfd});
        data->clientHandler->handleClient(is, os);
        ::close(clientfd);
    }

    delete data;
    return nullptr;
}

bool MySerialServer::acceptClients(ClientHandler* handler) {
    ServerData* data = new ServerData{ handler->copy(), _open, _sockfd, 5, 0 };

    if (pthread_create(&threadId, NULL, parallelHandle, data)) {
        perror("ERROR creating thread.");
        delete data;
        return false;
    }

    return true;
}