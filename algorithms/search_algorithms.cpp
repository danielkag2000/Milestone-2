#include "search_algorithms.h"
#include <stack>
#include <set>
#include <queue>

template <class T>
list<State<T>> Searcher<T>::createStateList(State<T> endState) {
    list<State<T>> stateList;
    State<T> current = endState;
    stateList.push_front(current);

    while (current.getParent() != nullptr) {
        current = current.getParent();
        stateList.push_front(current);
    }
    return stateList;
}

template <class T>
State<T> DFS<T>::make_search(Searchable<T>* searcher) {
    list<State<T>> open;  // will be treated as a stack
    set<State<T>> close;
    State<T> current;

    open.push_back(searcher->getInitialState());
    while (!open.empty()) {
        current = open.pop_back();
        close.insert(current);

        if (current == searcher->getGoalState()) {
            return current;
        }

        for (State<T>& s : searcher->getAllPossibleStates(current)) {
            if (close.find(s) == close.end() && find(open.begin(), open.end(), s) == open.end()) {
                s.setParent(current);
                open.push_back(s);
            }
        }
    }
}

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
            if (close.find(s) == close.end() && find(open.begin(), open.end(), s) == open.end()) {
                s.setParent(current);
                open.push_back(s);
            }
        }
    }
}


template <class T>
State<T> BestFirstSearch<T>::make_search(Searchable<T>* searcher) {
    auto comparator = [](const State<T>& s1, const State<T>& s2) { return h(s1) - h(s2); };
    priority_queue<State<T>> open(comparator);
    set<State<T>> close;
    State<T> current;

    open.push(searcher->getInitialState());
    while (!open.empty()) {
        current = open.pop();
        close.insert(current);

        if (current == searcher->getGoalState()) {
            return current;
        }

        for (State<T>& s : searcher->getAllPossibleStates(current)) {
            if (close.find(s) != close.end() && find(open.begin(), open.end(), s) != open.end()) {
                s.setParent(current);
                open.push(s);

            }
            // need to complete the else!!!
        }
    }
}


