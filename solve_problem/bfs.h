#ifndef MILESTONE_2_BFS_H
#define MILESTONE_2_BFS_H

#include "search_algorithms.h"

/**
 * the bfs searcher
 * @tparam T the state type
 */
template <class T>
class BFS : public Searcher<T> {
public:
    virtual ~BFS() {}

protected:
    virtual SearchInfo<T>* make_search(Searchable<T>* searcher) {
        list<Pointer<State<T>>> open;  // will be treated as a stack  (open)
        set<Pointer<State<T>>> close;  // the close list
        Pointer<State<T>> current;  // the current state
        int develop = 0;  // counter of develops

        open.push_back(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.front();
            open.pop_front();
            close.insert(current);

            // if this is the goal state
            if (*(*current) == searcher->getGoalState()) {
                SearchInfo<T>* si = new SearchInfo<T>(*current, develop);
                deletePointers(open);
                deletePointers(close);
                return si;
            }

            develop++;  // develop
            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end() && find(open.begin(), open.end(), Pointer<State<T>>(&s)) == open.end()) {
                    s.setParent(*current);
                    open.push_back(new State<T>(s));
                }
            }
        }
        // not found a path
        deletePointers(open);
        deletePointers(close);
        return new SearchInfo<T>(nullptr, develop);
    }
};

#endif //MILESTONE_2_BFS_H
