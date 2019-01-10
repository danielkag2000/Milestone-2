#ifndef MILESTONE_2_SERVER_H
#define MILESTONE_2_SERVER_H

#include "clientHandler.h"

namespace server_side {
    class Server {
    public:
        /**
         * Open this server.
         * @param port the port to open on
         * @param clientHandler a client handler
         * @return true if opened successfully, false otherwise.
         */
        virtual bool open(int port, ClientHandler* ch) = 0;

        /**
         * Close this server.
         */
        virtual void close() = 0;

        /**
         * Query whether this server is open.
         * @return true if it, is false otherwise.
         */
        virtual bool isOpen() = 0;

        /**
         * Destructor.
         */
        virtual ~Server() = default;
    };
}

#endif
