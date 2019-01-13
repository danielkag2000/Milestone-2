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
#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
void deletePointers(T begin, T end) {
    while (begin != end) {
        delete *(*begin);
        begin++;
    }
}

template<class structure>
void deletePointers(const structure& s) {
    deletePointers(s.cbegin(), s.cend());
}

template <class T>
class SearchInfo {
    int cost;
    int develope;
    list<T> path;

    list<T> createStateList(State<T>* endState) {
        list<T> stateList;

        // if there is a path
        if (endState != nullptr) {
            State<T> *current = endState;
            stateList.push_front(current->getValue());

            while (current->getParent() != nullptr) {
                current = current->getParent();
                stateList.push_front(current->getValue());
            }
        }
        return stateList;
    }


public:
    SearchInfo(State<T>* last, int developedNodes) {
        if (last == nullptr) {
            this->cost = -1;
        } else {
            this->cost = last->getCost();
        }
        this->develope = developedNodes;
        path = createStateList(last);
    }
    int getCost() { return this->cost; }
    int getNumOfDevelopeNodes() { return this->develope; }
    list<T> getPath() { return this->path; }
};




template <class T>
using GraphSearch = algorithm::Solver<Searchable<T>*, SearchInfo<T>*>;


template <class T>
class Searcher : public GraphSearch<T> {
public:
    virtual SearchInfo<T>* solve(Searchable<T>* searcher) {
        return make_search(searcher);
    }
    virtual ~Searcher() {}

protected:
    virtual SearchInfo<T>* make_search(Searchable<T>* searcher) = 0;
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

    ~Pointer() { }
};




template <class T>
class DFS : public Searcher<T> {
public:
    virtual ~DFS() {}

protected:
    virtual SearchInfo<T>* make_search(Searchable<T>* searcher) {
        list<Pointer<State<T>>> open;  // will be treated as a stack
        set<Pointer<State<T>>> close;
        Pointer<State<T>> current;
        int develop = 0;

        open.push_back(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.back();
            open.pop_back();
            close.insert(current);
            develop++;

            if (*(*current) == searcher->getGoalState()) {
                //cout << develop << endl;
                return new SearchInfo<T>(*current, develop);
            }

            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end()) {
                    s.setParent(*current);
                    open.push_back(new State<T>(s));
                }
            }
        }
        return new SearchInfo<T>(nullptr, develop);
    }
};




template <class T>
class BFS : public Searcher<T> {
public:
    virtual ~BFS() {}

protected:
    virtual SearchInfo<T>* make_search(Searchable<T>* searcher) {
        list<Pointer<State<T>>> open;  // will be treated as a stack
        set<Pointer<State<T>>> close;
        Pointer<State<T>> current;
        int develop = 0;

        open.push_back(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.front();
            open.pop_front();
            close.insert(current);
            develop++;

            if (*(*current) == searcher->getGoalState()) {
                //cout << develop << endl;
                return new SearchInfo<T>(*current, develop);
            }

            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end() && find(open.begin(), open.end(), Pointer<State<T>>(&s)) == open.end()) {
                    s.setParent(*current);
                    open.push_back(new State<T>(s));
                }
            }
        }
        return new SearchInfo<T>(nullptr, develop);
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
    virtual SearchInfo<T>* make_search(Searchable<T>* searcher) = 0;
};






template <class T>
class BestFirstSearch : public HeuristicSearcher<T> {
public:
    BestFirstSearch(HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~BestFirstSearch() {}
protected:
    virtual SearchInfo<T>* make_search(Searchable<T>* searcher) {
        auto& func = HeuristicSearcher<T>::h;
        auto comparator = [&func](const Pointer<State<T>>& s1, const Pointer<State<T>>& s2) { return func(*(*s1)) > func(*(*s2)); };
        priority_queue<Pointer<State<T>>, vector<Pointer<State<T>>>, decltype(comparator)> open(comparator);
        set<Pointer<State<T>>> close;
        Pointer<State<T>> current;
        int develop = 0;

        open.push(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.top();
            open.pop();
            close.insert(current);
            develop++;

            if (*(*current) == searcher->getGoalState()) {
                //cout << develop << endl;
                return new SearchInfo<T>(*current, develop);
            }


            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end()) {
                    s.setParent(*current);
                    open.push(new State<T>(s));
                }
            }
        }
        return new SearchInfo<T>(nullptr, develop);
    }
};




template <class T>
class AStar : public HeuristicSearcher<T> {
public:
    AStar(HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~AStar() {}
protected:
    virtual SearchInfo<T>* make_search(Searchable<T>* searcher) {
        auto& func = HeuristicSearcher<T>::h;
        auto comparator = [&func](const Pointer<State<T>>& s1, const Pointer<State<T>>& s2) { return ((*s1)->getCost() + func(*(*s1))) > ((*s2)->getCost() + func(*(*s2))); };
        priority_queue<Pointer<State<T>>, vector<Pointer<State<T>>>, decltype(comparator)> open(comparator);
        set<Pointer<State<T>>> close;
        Pointer<State<T>> current;
        int develop = 0;

        open.push(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.top();
            open.pop();
            close.insert(current);
            develop++;

            if (*(*current) == searcher->getGoalState()) {
                //cout << develop << endl;
                return new SearchInfo<T>(*current, develop);
            }

            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end()) {
                    s.setParent(*current);
                    open.push(new State<T>(s));
                }
            }
        }
        return new SearchInfo<T>(nullptr, develop);
    }
};


#endif //MILESTONE_2_SEARCH_ALGORITHMS_H
