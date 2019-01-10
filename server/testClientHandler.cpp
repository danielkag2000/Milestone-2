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

    void MyTestClientHandler::handleClient(server_side::Client client) {
        vector<char> vec;

        vec.resize(20);
        ssize_t read = client.read(vec, 20);

        auto it = vec.begin();
        while (read-- > 0) {
            cout << *it;
            it++;
        }

        cout << endl;

        client.write(vec, 20);

        cout << "wrote to client" << endl;
    }

    void MyTestClientHandler::handleClient(istream &is, ostream &os) {
        string x;

        getline(is, x);

        cout << "sending: " << x << endl;
        os << x;
    }
}