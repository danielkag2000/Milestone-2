#ifndef MILESTONE_2_SEARCH_ALGORITHMS_H
#define MILESTONE_2_SEARCH_ALGORITHMS_H

#include "solver.h"
#include "searchable.h"
#include <list>

using namespace algorithm;
using namespace std;

template <class T>
using GraphSearch = Solver<Searchable<T>*, list<State<T>>>;


template <class T>
class Searcher : public GraphSearch<T> {
    virtual list<State<T>> solve(Searchable<T>* searcher) {
        return createStateList(make_search(searcher));
    }
    virtual ~Searcher() {}

protected:
    virtual State<T> make_search(Searchable<T>* searcher) = 0;
    virtual list<State<T>> createStateList(State<T> endState);
};


template <class T>
class DFS : public Searcher<T> {
    virtual State<T> make_search(Searchable<T>* searcher);

    virtual ~DFS() {}
};


#endif
