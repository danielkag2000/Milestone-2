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

/**
 *
 * @tparam T the iterator type
 * @param begin the iterator to the beginning
 * @param end the iterator to the end
 */
template<class T>
void deletePointers(T begin, T end) {
    while (begin != end) {
        delete *(*begin);
        begin++;
    }
}

/**
 *
 * @tparam structure the structure type
 * @param s the data structure
 */
template<class structure>
void deletePointers(const structure& s) {
    deletePointers(s.cbegin(), s.cend());
}

/**
 * the solution of the search
 * @tparam T the type of the state
 */
template <class T>
class SearchInfo {
    int cost;
    int develope;
    list<T> path;

    /**
     * create the path
     * @param endState the solution state
     * @return the list of the values
     */
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

/**
 * the searcher
 * @tparam T the type of the state
 */
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



/**
 * represent a pointer class
 * @tparam T the type of the value
 */
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


/**
 * delete the queue
 * @tparam structure the structure type
 * @param s the queue
 */
template<class structure>
void deleteQueue(structure& s) {

    while (!s.empty()) {
        auto var = *(s.top());
        s.pop();
        delete var;
    }
}






/**
 * represent Heuristic Function
 * @tparam T the state type
 */
template <class T>
class HeuristicFunction {
protected:
    const State<T> goal;
public:
    HeuristicFunction(const State<T> goal_state) : goal(goal_state) {}

    virtual double operator()(const State<T>& current) const = 0;
};



/**
 * Heuristic Function of Manhattan Distance
 */
class ManhattanDistance : public HeuristicFunction<pair<int, int>> {
public:
    ManhattanDistance(const State<pair<int, int>> goal_state) : HeuristicFunction(goal_state) {}

    double operator()(const State<pair<int, int>>& current) const {
        return abs(current.getValue().first - goal.getValue().first)
               + abs(current.getValue().second - goal.getValue().second);
    }
};



/**
 * a searcher that using Heuristic Function
 * @tparam T the state type
 */
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


#endif //MILESTONE_2_SEARCH_ALGORITHMS_H
