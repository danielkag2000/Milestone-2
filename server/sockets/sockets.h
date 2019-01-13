#ifndef MILESTONE_2_SOCKETS_H
#define MILESTONE_2_SOCKETS_H

#include "socket_exceptions.h"

namespace posix_sockets {
    class TCPSocket {
    private:
        int _sockfd;

    public:
        TCPSocket();

        TCPSocket(int sockfd);

        void close();

        void setTimeout(int sec, int usec = 0);

        int fd();
    };

    class TCPServer {
    private:
        TCPSocket _sock;
    public:
        TCPServer(int port);

        void listen(int max_lis);

        void setTimeout(int sec, int usec = 0);

        TCPSocket accept();

        void close();
    };
}

#endif
