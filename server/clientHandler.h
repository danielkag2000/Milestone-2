#ifndef MILESTONE_2_CLIENTHANDLER_H
#define MILESTONE_2_CLIENTHANDLER_H

#include <ios>

using namespace std;

namespace server_side {
    class ClientHandler {
    public:
        virtual void handleClient(istream& is, ostream& os) = 0;
    };
}

#endif
