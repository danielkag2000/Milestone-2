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
public:
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
public:
    virtual ~DFS() {}

protected:
    virtual State<T> make_search(Searchable<T>* searcher);
};

template <class T>
class BFS : public Searcher<T> {
public:
    virtual ~BFS() {}

protected:
    virtual State<T> make_search(Searchable<T>* searcher);
};



template <class T>
class HeuristicFunction {
public:
    double operator()(State<T> current, State<T> goal) = 0;
};


template <class T>
class HeuristicSearcher : public Searcher<T> {

private:
    const HeuristicFunction<T>& h;

public:
    HeuristicSearcher(const HeuristicFunction<T>& h) : h(h) {}
    virtual ~HeuristicSearcher() {}

protected:
    virtual State<T> make_search(Searchable<T>* searcher) = 0;
};

template <class T>
class BestFirstSearch : public Searcher<T> {
public:
    BestFirstSearch(const HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~BestFirstSearch() {}

protected:
    virtual State<T> make_search(Searchable<T>* searcher);
};


#endif
