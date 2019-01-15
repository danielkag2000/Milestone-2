#ifndef MILESTONE_2_TESTCLIENTHANDLER_H
#define MILESTONE_2_TESTCLIENTHANDLER_H

#include "clientHandler.h"
#include "../solve_problem/solver.h"
#include "../cache/fileCacheManager.h"
#include "../cache/stringCacheManager.h"

namespace server_side {
    typedef cache::StringCacheManager CM;
    typedef algorithm::Solver<const string*, string> SOLVER;

    class MyTestClientHandler : public ClientHandler {
    private:
        SOLVER* _solver;
        CM* _cache;

        MyTestClientHandler(SOLVER* solver, CM* cache);
    public:
        MyTestClientHandler();

        //virtual void handleClient(Client client);

        virtual void handleClient(istream& is, ostream& os);

        virtual ClientHandler* copy() {
            return new MyTestClientHandler(_solver, _cache);
        }

        void free() {
            delete _solver;
            delete _cache;
        }
    };
}


#endif