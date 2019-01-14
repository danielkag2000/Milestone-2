#include "testClientHandler.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

#include "../solve_problem/solver.h"

using namespace cache;

namespace server_side {
    class StringReverser : public algorithm::Solver<const string*,string> {
        string solve(const string *str) {
            string cpy(*str);
            reverse(cpy.begin(), cpy.end());
            return cpy;
        }
    };


    class StringStreamer : public Streamer<string> {
        virtual std::string serialize(const string* instance) {
            return *instance;
        }

        virtual string* deserialize(const std::string& str) {
            return new string(str);
        }

        virtual ~StringStreamer() = default;
    };

    MyTestClientHandler::MyTestClientHandler(SOLVER* solver, CM* cm) :
        _solver(solver),
        _cache(cm) {

    }

    MyTestClientHandler::MyTestClientHandler() :
            _solver(new StringReverser),
            _cache(new FileCacheManager<string, string>(new DefaultPSS<string, string>(new StringStreamer, new StringStreamer))){

    }


    void MyTestClientHandler::handleClient(istream &is, ostream &os) {
        string s;

        do {
            getline(is, s);

            if (_cache->solutionExists(&s)) {
                os << *_cache->getSolution(&s);
            }
            else {
                string sol(_solver->solve(&s));
                _cache->saveSolution(new string(s), new string(sol));
                os << sol;
            }


        }
        while (s != "end" && !is.eof());
    }
}