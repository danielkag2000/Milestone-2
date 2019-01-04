#ifndef MILESTONE_2_SERVER_H
#define MILESTONE_2_SERVER_H

#include "clientHandler.h"

namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler* ch) = 0;
        virtual void close() = 0;

        virtual bool isOpen() = 0;

        virtual ~Server() = default;
    };
}

#endif
