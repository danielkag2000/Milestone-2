#ifndef MILESTONE_2_DFS_H
#define MILESTONE_2_DFS_H

#include "search_algorithms.h"

/**
 * the dfs searcher
 * @tparam T the state type
 */
template <class T>
class DFS : public Searcher<T> {
public:
    virtual ~DFS() {}

protected:
    virtual SearchInfo<T>* make_search(Searchable<T>* searcher) {
        list<Pointer<State<T>>> open;  // will be treated as a stack (open)
        set<Pointer<State<T>>> close;  // the close list
        Pointer<State<T>> current;  // the current state
        int develop = 0;  // counter of develops

        open.push_back(Pointer<State<T>>(new State<T>(searcher->getInitialState())));
        while (!open.empty()) {
            current = open.back();
            open.pop_back();
            close.insert(current);

            // if this is the goal state
            if (*(*current) == searcher->getGoalState()) {
                SearchInfo<T>* si = new SearchInfo<T>(*current, develop);
                deletePointers(open);
                deletePointers(close);
                return si;
            }

            develop++;  // develop
            list<State<T>> develop_list = searcher->getAllPossibleStates(*(*current));
            develop_list.reverse();  // because we get the develops from the last to the end
            for (State<T>& s : develop_list) {
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

#endif //MILESTONE_2_DFS_H
