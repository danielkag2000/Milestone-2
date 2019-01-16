#ifndef MILESTONE_2_A_STAR_H
#define MILESTONE_2_A_STAR_H

#include "search_algorithms.h"

/**
 * the A* searcher
 * @tparam T the state type
 */
template <class T>
class AStar : public HeuristicSearcher<T> {
public:
    AStar(HeuristicFunction<T>& h) : HeuristicSearcher<T>(h) {}
    virtual ~AStar() {}

    virtual SearchInfo<T>* make_search(Searchable<T>* searcher) const {

        // set the goal state
        HeuristicSearcher<T>::h.setGoal(searcher->getGoalState());
        auto& func = HeuristicSearcher<T>::h;  // the Heuristic function
        // the comparator (f(n) = g(n) + h(n) = cost + h(n))
        auto comparator = [&func](const Pointer<State<T>>& s1, const Pointer<State<T>>& s2) { return ((*s1)->getCost() + func(*(*s1))) > ((*s2)->getCost() + func(*(*s2))); };
        // the priority queue (open list)
        priority_queue<Pointer<State<T>>, vector<Pointer<State<T>>>, decltype(comparator)> open(comparator);
        set<Pointer<State<T>>> close;  // the close list
        Pointer<State<T>> current;  // the current state

        open.push(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.top();
            open.pop();
            close.insert(current);

            // if this is the goal state
            if (*(*current) == searcher->getGoalState()) {
                SearchInfo<T>* si = new SearchInfo<T>(*current, close.size());
                deleteQueue(open);
                deletePointers(close);
                return si;
            }

            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end()) {
                    s.setParent(*current);
                    open.push(new State<T>(s));
                }
            }
        }
        // not found a path
        int develop = close.size();  // counter of develops
        deleteQueue(open);
        deletePointers(close);
        return new SearchInfo<T>(nullptr, develop);
    }
};

#endif
