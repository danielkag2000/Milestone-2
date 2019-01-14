#ifndef MILESTONE_2_SEARCH_SOLVER_H
#define MILESTONE_2_SEARCH_SOLVER_H

#include "solver.h"
#include "a_star.h"
#include "best_first_search.h"
#include "bfs.h"
#include "dfs.h"
#include <unordered_map>

namespace algorithm {

    /**
     * a search solver
     * @tparam T the type of the state
     */
    template <class T>
    class SearchSolver : public Solver<Searchable<T>*, SearchInfo<T>*> {
        const Searcher<T>* search_algoritm;

    public:
        SearchSolver(const Searcher<T>* alg) { this->search_algoritm = alg; }

        virtual SearchInfo<T>* solve(Searchable<T>* searchProb) {
            return search_algoritm->make_search(searchProb);
        }

        ~SearchSolver() { delete search_algoritm; }
    };
}

#endif
