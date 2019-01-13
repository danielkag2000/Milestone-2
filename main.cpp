#include <iostream>
#include "solve_problem/search_algorithms.h"
#include "test.h"
#include <vector>
#include "server/parallelServer.h"
#include "server/testClientHandler.h"

namespace boot {
    int main() {
        using namespace server_side;

        Server* s = new ParallelServer;
        ClientHandler* ch = new MyTestClientHandler;

        s->open(25565, ch);

        int x;
        cin >> x;

        s->close();

        return 0;
    }

    int main2() {
        //std::cout << "Hello, World!" << std::endl;
        //BFS< bfs = new BFS()

        vector<vector<int>> table = {
                { 4, 2, 9, 5, 7, 0, 7, 6, 3, 7, 8},
                { 4, 0,10, 8, 1, 0, 5, 5, 7, 8, 4},
                { 4, 5, 2, 8, 1, 1, 9, 3, 3, 0, 7},
                { 3, 3, 6, 2, 8, 9, 6, 8, 3, 5, 7},
                { 0, 3, 7, 3, 7,10, 4, 8, 9, 1, 1},
                { 7, 3, 2, 3, 5, 0, 2, 1, 6, 0, 9},
                { 6, 9, 8, 1,10, 3, 9, 8, 3, 4, 8},
                {10, 8, 0, 2, 3, 8, 0,10,10, 2, 7},
                { 5, 7, 0, 8, 8, 8, 0, 3, 4, 5, 1},
                { 7, 7, 5,10, 8,10, 1, 6, 9, 9, 1},
                { 5,10, 1,10, 7, 7, 3,10, 8, 0, 6}};

/*        vector<vector<int>> table = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
*/
        TableGraph* t = new TableGraph(table);

        ManhattanDistance mh = ManhattanDistance(State<pInt>({11, 11}));
        AStar<pInt>* alg = new AStar<pInt>(mh);
        //BestFirstSearch<pInt>* alg = new BestFirstSearch<pInt>(mh);
        //BFS<pInt>* alg = new BFS<pInt>();
        //DFS<pInt>* alg = new DFS<pInt>();
        SearchInfo<pInt>* s = alg->solve(t);

        list<pInt> l = s->getPath();
        for (pInt p : l) {
            cout << p.first << ", " << p.second <<endl;
        }
        cout << "with the cost of: " << s->getCost() << endl;

        delete alg;

        return 0;
    }
}

int main() {
    return boot::main();
}