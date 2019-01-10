#ifndef MILESTONE_2_TESTCLIENTHANDLER_H
#define MILESTONE_2_TESTCLIENTHANDLER_H

#include "clientHandler.h"
#include "../solve_problem/solver.h"

namespace server_side {
    class MyTestClientHandler : public ClientHandler {
    private:
        algorithm::Solver<const string*, string>* _solver;
    public:
        MyTestClientHandler();

        virtual void handleClient(Client client);

        virtual void handleClient(istream& is, ostream& os);

        virtual ClientHandler* copy() {
            return new MyTestClientHandler;
        }
    };
}


#endif