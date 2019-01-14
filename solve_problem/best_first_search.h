#ifndef MILESTONE_2_BEST_FIRST_SEARCH_H
#define MILESTONE_2_BEST_FIRST_SEARCH_H

#include "search_algorithms.h"

/**
 * the best first search searcher
 * @tparam T the state type
 */
template <class T>
class BestFirstSearch : public HeuristicSearcher<T> {
public:
    BestFirstSearch(HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~BestFirstSearch() {}
protected:
    virtual SearchInfo<T>* make_search(Searchable<T>* searcher) {
        auto& func = HeuristicSearcher<T>::h;  // the Heuristic function
        // the comparator (f(n) = h(n))
        auto comparator = [&func](const Pointer<State<T>>& s1, const Pointer<State<T>>& s2) { return func(*(*s1)) > func(*(*s2)); };
        // the priority queue (open list)
        priority_queue<Pointer<State<T>>, vector<Pointer<State<T>>>, decltype(comparator)> open(comparator);
        set<Pointer<State<T>>> close;  // the close list
        Pointer<State<T>> current;  // the current state
        int develop = 0;  // counter of develops

        open.push(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.top();
            open.pop();
            close.insert(current);

            // if this is the goal state
            if (*(*current) == searcher->getGoalState()) {
                SearchInfo<T>* si = new SearchInfo<T>(*current, develop);
                deleteQueue(open);
                deletePointers(close);
                return si;
            }

            develop++;  // develop
            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end()) {
                    s.setParent(*current);
                    open.push(new State<T>(s));
                }
            }
        }
        // not found a path
        deleteQueue(open);
        deletePointers(close);
        return new SearchInfo<T>(nullptr, develop);
    }
};

#endif
