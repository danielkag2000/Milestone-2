
#include "search_algorithms.h"
#include <stack>
#include <set>
#include <queue>

/*template <class T>
State<T>* DFS<T>::make_search(Searchable<T>* searcher) {
    list<State<T>> open;  // will be treated as a stack
    set<State<T>> close;
    State<T> current;

    open.push_back(searcher->getInitialState());
    while (!open.empty()) {
        current = open.pop_back();
        close.insert(current);

        if (current == searcher->getGoalState()) {
            return move(current);
        }

        for (State<T>& s : searcher->getAllPossibleStates(current)) {
            if (close.find(s) == close.end()) {
                s.setParent(&current);
                open.push_back(s);
            }
        }
    }
}*/

/*
template <class T>
State<T> BFS<T>::make_search(Searchable<T>* searcher) {
    list<State<T>> open;  // will be treated as a stack
    set<State<T>> close;
    State<T> current;

    open.push_back(searcher->getInitialState());
    while (!open.empty()) {
        current = open.pop_front();
        close.insert(current);

        if (current == searcher->getGoalState()) {
            return current;
        }

        for (State<T>& s : searcher->getAllPossibleStates(current)) {
            if (close.find(s) == close.end()) {
                s.setParent(&current);
                open.push_back(s);
            }
        }
    }
}
*/



template <class T>
State<T>* BestFirstSearch<T>::make_search(Searchable<T>* searcher) {
    auto comparator = [](const State<T>& s1, const State<T>& s2) { return h(s1) - h(s2); };
    priority_queue<State<T>, vector<State<T>>, decltype(comparator)> open(comparator);
    set<State<T>> close;
    State<T> current;

    open.push(searcher->getInitialState());
    while (!open.empty()) {
        current = open.pop();

        if (current == searcher->getGoalState()) {
            return move(current);
        }

        for (State<T>& s : searcher->getAllPossibleStates(current)) {
            if (close.find(s) != close.end()) {
                s.setParent(&current);
                open.push(s);
                close.insert(current);
            }
        }
    }
    return nullptr;
}




template <class T>
State<T>* AStar<T>::make_search(Searchable<T>* searcher) {
    auto comparator = [](const State<T>& s1, const State<T>& s2) { return (s1.getCost() + h(s1)) - (s2.getCost() + h(s2)); };
    priority_queue<State<T>, vector<State<T>>, decltype(comparator)> open(comparator);
    set<State<T>> close;
    State<T> current;

    open.push(searcher->getInitialState());
    while (!open.empty()) {
        current = open.pop();

        if (current == searcher->getGoalState()) {
            return move(current);
        }

        for (State<T>& s : searcher->getAllPossibleStates(current)) {
            if (close.find(s) != close.end()) {
                s.setParent(current);
                open.push(s);
                close.insert(current);
            }
        }
    }
    return nullptr;
}
