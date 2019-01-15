#ifndef MILESTONE_2_MY_CLIENT_HANDLER_H
#define MILESTONE_2_MY_CLIENT_HANDLER_H

#include "clientHandler.h"
#include "../solve_problem/searchable_table.h"
#include "../solve_problem/search_solver.h"
#include "../solve_problem/a_star.h"
#include "../solve_problem/best_first_search.h"
#include "../solve_problem/dfs.h"
#include "../solve_problem/bfs.h"
#include "../cache/stringCacheManager.h"
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

    void addSolver(string name, algorithm::SearchSolver<T>* alg) {
        this->algorithmSolverHolder.insert(make_pair(name, alg));
    }

    algorithm::SearchSolver<T>* getSolver(string name) {
        return this->algorithmSolverHolder[name];
    }

    ~AlgorithmSolverHolder() {
        for (auto& alg : algorithmSolverHolder) {
            delete alg.second;
        }
    }
};


namespace server_side {

    class MyClientHandler : public ClientHandler {
    private:
        AlgorithmSolverHolder<pInt> solverHolder;
        ManhattanDistance mh;
        cache::StringCacheManager* cm;

        string findSolution(SearchableTable* table, size_t size);

        MyClientHandler(cache::StringCacheManager* cm) : cm(cm) { }
    public:
        MyClientHandler() : solverHolder(), mh() {
            typedef algorithm::SearchSolver<pInt> SS;

            solverHolder.addSolver("BFS", new SS(new BFS<pInt>()));
            solverHolder.addSolver("DFS", new SS(new DFS<pInt>()));
            solverHolder.addSolver("AStar", new SS(new AStar<pInt>(mh)));
            solverHolder.addSolver("BestFirstSearch", new SS(new BestFirstSearch<pInt>(mh)));

            cm = new cache::StringCacheManager();
        }

        virtual ClientHandler* copy() { return new MyClientHandler(cm); }

        virtual void handleClient(istream& is, ostream& os);

        virtual ~MyClientHandler() = default;

        void closeCache() {
            delete cm;
        }
    };
}


#endif
