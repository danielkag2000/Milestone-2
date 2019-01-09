#ifndef MILESTONE_2_SERIALSERVER_H
#define MILESTONE_2_SERIALSERVER_H

#include "server.h"
#include "clientHandler.h"

class MySerialServer : public server_side::Server {

public:

    virtual void open(int port, server_side::ClientHandler* clientHandler);
    virtual void close();

    virtual ~MySerialServer() { close(); }
};

#endif
