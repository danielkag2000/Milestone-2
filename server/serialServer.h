#ifndef MILESTONE_2_SERIALSERVER_H
#define MILESTONE_2_SERIALSERVER_H

#include "server.h"
#include "clientHandler.h"

using namespace server_side;

class MySerialServer : public Server {

public:

    virtual void open(int port, ClientHandler* clientHandler) override;
    virtual void close() override;

    virtual ~MySerialServer() override { }
};

#endif
