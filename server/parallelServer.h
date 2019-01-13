//
// Created by Evyatar on 1/13/2019.
//

#ifndef MILESTONE_2_PARALLELSERVER_H
#define MILESTONE_2_PARALLELSERVER_H

#include "server.h"
#include "threads/threads.h"

namespace server_side {
    class ParallelServer : public Server {
    private:
        bool _open;
        threads::Thread* _serverThread;
    public:
        ParallelServer() : _serverThread(nullptr) { }

        virtual bool open(int port, ClientHandler* ch);

        virtual void close();

        virtual bool isOpen();
    };
}


#endif //MILESTONE_2_PARALLELSERVER_H
