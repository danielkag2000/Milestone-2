#ifndef MILESTONE_2_MY_CLIENT_HANDLER_H
#define MILESTONE_2_MY_CLIENT_HANDLER_H

#include "clientHandler.h"
#include "../solve_problem/searchable_table.h"
#include "../solve_problem/search_solver.h"
#include "../solve_problem/a_star.h"
#include "../solve_problem/best_first_search.h"
#include "../solve_problem/dfs.h"
#include "../solve_problem/bfs.h"
#include <unordered_map>

template <class T>
using solver_map = unordered_map<string, algorithm::SearchSolver<T>*>;

/**
 * Holder of the algorithms Algorithms solvers
 * @tparam T the state type
 */
template <class T>
class AlgorithmSolverHolder {
    solver_map<T> algorithmSolverHolder;

public:
    AlgorithmSolverHolder() {}

    void addSolver(string name, algorithm::SearchSolver<T>* alg) { this->algorithmSolverHolder.insert(make_pair(name, alg)); }

    algorithm::SearchSolver<T>* getSolver(string name) { return this->algorithmSolverHolder[name]; }

    ~AlgorithmSolverHolder() {
        for (typename solver_map<T>::iterator it = algorithmSolverHolder.begin(); it != algorithmSolverHolder.end(); ++it) {
            delete it->second;
        }
    }
};


namespace server_side {

    class MyClientHandler : public ClientHandler {
        AlgorithmSolverHolder<pInt>* solverHolder;
        ManhattanDistance mh;

    public:
        MyClientHandler() {
            this->solverHolder = new AlgorithmSolverHolder<pInt>();
            solverHolder->addSolver("BFS", new algorithm::SearchSolver<pInt>(new BFS<pInt>()));
            solverHolder->addSolver("BFS", new algorithm::SearchSolver<pInt>(new DFS<pInt>()));
            this->mh = ManhattanDistance();
            solverHolder->addSolver("AStar", new algorithm::SearchSolver<pInt>(new AStar<pInt>(mh)));
            solverHolder->addSolver("BestFirstSearch", new algorithm::SearchSolver<pInt>(new BestFirstSearch<pInt>(mh)));
        }

        virtual ClientHandler* copy() { return new MyClientHandler(); }

        virtual void handleClient(istream& is, ostream& os);

        virtual ~MyClientHandler() { delete solverHolder; }
    };
}


#endif
