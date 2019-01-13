#ifndef MILESTONE_2_DFS_H
#define MILESTONE_2_DFS_H

#include "search_algorithms.h"

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
                SearchInfo<T>* si = new SearchInfo<T>(*current, develop);
                deletePointers(open);
                deletePointers(close);
                return si;
            }

            list<State<T>> develop_list = searcher->getAllPossibleStates(*(*current));
            develop_list.reverse();
            for (State<T>& s : develop_list) {
                if (close.find(&s) == close.end() && find(open.begin(), open.end(), Pointer<State<T>>(&s)) == open.end()) {
                    s.setParent(*current);
                    open.push_back(new State<T>(s));
                }
            }
        }
        deletePointers(open);
        deletePointers(close);
        return new SearchInfo<T>(nullptr, develop);
    }
};

#endif //MILESTONE_2_DFS_H
