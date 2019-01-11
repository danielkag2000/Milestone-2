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
    int getCost() { return this->cost; }
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
        return nullptr;
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
        return nullptr;
    }
};






template <class T>
class HeuristicFunction {
protected:
    const State<T> goal;
public:
    HeuristicFunction(const State<T> goal_state) : goal(goal_state) {}

    virtual double operator()(const State<T>& current) const = 0;
};

class ManhattanDistance : public HeuristicFunction<pair<int, int>> {
public:
    ManhattanDistance(const State<pair<int, int>> goal_state) : HeuristicFunction(goal_state) {}

    double operator()(const State<pair<int, int>>& current) const {
        return abs(current.getValue().first - goal.getValue().first)
               + abs(current.getValue().second - goal.getValue().second);
    }
};




template <class T>
class HeuristicSearcher : public Searcher<T> {
protected:
    HeuristicFunction<T>& h;
public:
    HeuristicSearcher(HeuristicFunction<T>& h) : h(h) {}
    virtual ~HeuristicSearcher() {}
protected:
    virtual State<T>* make_search(Searchable<T>* searcher) = 0;
};






template <class T>
class BestFirstSearch : public HeuristicSearcher<T> {
public:
    BestFirstSearch(HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~BestFirstSearch() {}
protected:
    virtual State<T>* make_search(Searchable<T>* searcher) {
        auto& func = HeuristicSearcher<T>::h;
        auto comparator = [&func](const Pointer<State<T>>& s1, const Pointer<State<T>>& s2) { return func(*(*s1)) > func(*(*s2)); };
        priority_queue<Pointer<State<T>>, vector<Pointer<State<T>>>, decltype(comparator)> open(comparator);
        set<Pointer<State<T>>> close;
        Pointer<State<T>> current;

        open.push(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.top();
            open.pop();
            close.insert(current);

            if (*(*current) == searcher->getGoalState()) {
                return *current;
            }


            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end()) {
                    s.setParent(*current);
                    open.push(new State<T>(s));
                }
            }
        }
        return nullptr;
    }
};




template <class T>
class AStar : public HeuristicSearcher<T> {
public:
    AStar(HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~AStar() {}
protected:
    virtual State<T>* make_search(Searchable<T>* searcher) {
        auto& func = HeuristicSearcher<T>::h;
        auto comparator = [&func](const Pointer<State<T>>& s1, const Pointer<State<T>>& s2) { return ((*s1)->getCost() + func(*(*s1))) > ((*s2)->getCost() + func(*(*s2))); };
        priority_queue<Pointer<State<T>>, vector<Pointer<State<T>>>, decltype(comparator)> open(comparator);
        set<Pointer<State<T>>> close;
        Pointer<State<T>> current;

        open.push(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.top();
            open.pop();
            close.insert(current);

            if (*(*current) == searcher->getGoalState()) {
                return *current;
            }

            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end()) {
                    s.setParent(*current);
                    open.push(new State<T>(s));
                }
            }
        }
        return nullptr;
    }
};


#endif //MILESTONE_2_SEARCH_ALGORITHMS_H
