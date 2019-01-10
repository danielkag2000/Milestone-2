//
// Created by Daniel on 1/9/2019.
//

#ifndef MILESTONE_2_SEARCH_ALGORITHMS_H
#define MILESTONE_2_SEARCH_ALGORITHMS_H

#include "solver.h"
#include "searchable.h"
#include <list>
#include <stack>
#include <unordered_set>
#include <set>
#include <queue>

using namespace std;

template <class T>
class SearchInfo {
    int cost;
    //int develope;
    list<T> path;

    list<T> createStateList(State<T>* endState) {
        list<T> stateList;
        State<T>* current = endState;
        stateList.push_front(current->getValue());

        while (current->getParent() != nullptr) {
            current = current->getParent();
            stateList.push_front(current->getValue());
        }
        return stateList;
    }


public:
    SearchInfo(State<T>* last) {
        this->cost = last->getCost();
        //this->develope = developedNodes;
        //this->path = path;
        path = createStateList(last);
    }
    //int getCost() { return this->cost; }
    //int getNumOfDevelopeNodes() { return this->develope; }
    list<T> getPath() { return this->path; }
};


template <class T>
State<T>* move(State<T>& s) {
    State<T>* last = new State<T>(s);
    State<T>* current = last;
    State<T>* par;

    while (current->getParent() != nullptr) {
        par = new State<T>(current->getParent());
        current->setParent(par);
        current = par;
    }
}




template <class T>
using GraphSearch = algorithm::Solver<Searchable<T>*, SearchInfo<T>*>;


template <class T>
class Searcher : public GraphSearch<T> {
public:
    virtual SearchInfo<T>* solve(Searchable<T>* searcher) {
        return new SearchInfo<T>(make_search(searcher));
    }
    virtual ~Searcher() {}

protected:
    virtual State<T>* make_search(Searchable<T>* searcher) = 0;
};




template<class T>
class Pointer {

private:
    T* ptr;

public:
    Pointer(T* ptr) : ptr(ptr) { }
    Pointer() : ptr(nullptr) { }

    bool operator<(const Pointer& ptr2) const {
        return *ptr < *(ptr2.ptr);
    }

    bool operator==(const Pointer& ptr2) const {
        return *ptr == *(ptr2.ptr);
    }

    T* operator*() const {
        return ptr;
    }

    //~Pointer() { delete ptr; }
};




template <class T>
class DFS : public Searcher<T> {
public:
    virtual ~DFS() {}

protected:
    virtual State<T>* make_search(Searchable<T>* searcher) {
        list<Pointer<State<T>>> open;  // will be treated as a stack
        set<Pointer<State<T>>> close;
        Pointer<State<T>> current;

        open.push_back(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.back();
            open.pop_back();
            close.insert(current);

            if (*(*current) == searcher->getGoalState()) {
                return *current;
            }

            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end()) {
                    s.setParent(*current);
                    open.push_back(new State<T>(s));
                }
            }
        }
    }
};




template <class T>
class BFS : public Searcher<T> {
public:
    virtual ~BFS() {}

protected:
    virtual State<T>* make_search(Searchable<T>* searcher) {
        list<Pointer<State<T>>> open;  // will be treated as a stack
        set<Pointer<State<T>>> close;
        Pointer<State<T>> current;

        open.push_back(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.front();
            open.pop_front();
            close.insert(current);

            if (*(*current) == searcher->getGoalState()) {
                return *current;
            }

            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end()) {
                    s.setParent(*current);
                    open.push_back(new State<T>(s));
                }
            }
        }
    }
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
    explicit HeuristicSearcher(const HeuristicFunction<T>& h) : h(h) {}
    virtual ~HeuristicSearcher() {}
protected:
    virtual State<T>* make_search(Searchable<T>* searcher) = 0;
};






template <class T>
class BestFirstSearch : public Searcher<T> {
public:
    explicit BestFirstSearch(const HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~BestFirstSearch() {}
protected:
    virtual State<T>* make_search(Searchable<T>* searcher);
};




template <class T>
class AStar : public Searcher<T> {
public:
    explicit AStar(const HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~AStar() {}
protected:
    virtual State<T>* make_search(Searchable<T>* searcher);
};


#endif //MILESTONE_2_SEARCH_ALGORITHMS_H
