#include "testClientHandler.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

#include "../solve_problem/solver.h"

namespace server_side {
    class StringReverser : public algorithm::Solver<const string*,string> {
        string solve(const string* str) {
            string cpy(*str);
            reverse(cpy.begin(), cpy.end());
            return cpy;
        }
    };

    MyTestClientHandler::MyTestClientHandler() : _solver(new StringReverser()) {}

    void MyTestClientHandler::handleClient(istream &is, ostream &os) {
        string s;

        do {
            getline(is, s);
            os << _solver->solve(&s);
        }
        while (s != "end" && !is.eof());
    }
}