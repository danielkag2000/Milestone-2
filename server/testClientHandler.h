#ifndef MILESTONE_2_TESTCLIENTHANDLER_H
#define MILESTONE_2_TESTCLIENTHANDLER_H

#include "clientHandler.h"

namespace server_side {
    class MyTestClientHandler : public ClientHandler {

        virtual void handleClient(istream& is, ostream& os);

        virtual ~MyTestClientHandler();
    };
}


#endif