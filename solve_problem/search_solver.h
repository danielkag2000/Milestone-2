#ifndef MILESTONE_2_SEARCH_SOLVER_H
#define MILESTONE_2_SEARCH_SOLVER_H

#include "solver.h"
#include "a_star.h"
#include "best_first_search.h"
#include "bfs.h"
#include "dfs.h"
#include <unordered_map>

template <class T>
unordered_map<string, Searcher<T>*> createSearchMap(HeuristicFunction<T>& h);

namespace algorithm {

    /**
     * a search solver
     * @tparam T the type of the state
     */
    template <class T>
    class SearchSolver : public Solver<Searchable<T>*, SearchInfo<T>*> {
        Searcher<T>* search_algoritm;

    public:
        SearchSolver(Searcher<T>* alg) { this->search_algoritm = alg; }

        virtual SearchInfo<T>* solve(Searchable<T>* searchProb) {
            return search_algoritm->make_search(searchProb);
        }

        ~SearchSolver() { }
    };
}

/**
 * make the map
 * @tparam T the state type
 * @param h the Heuristic Function
 * @return a map with the searchers
 */
template <class T>
unordered_map<string, Searcher<T>*> createSearchMap(HeuristicFunction<T>& h) {
    unordered_map<string, Searcher<T>*> search_map;

    search_map.insert(make_pair("Astar", new AStar<T>(h)));
    search_map.insert(make_pair("BestFirstSearch", new BestFirstSearch<T>(h)));
    search_map.insert(make_pair("BFS", new BFS<T>()));
    search_map.insert(make_pair("DFS", new DFS<T>()));

    return search_map;
}

#endif
