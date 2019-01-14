#ifndef MILESTONE_2_BEST_FIRST_SEARCH_H
#define MILESTONE_2_BEST_FIRST_SEARCH_H

#include "search_algorithms.h"

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

            if (*(*current) == searcher->getGoalState()) {
                SearchInfo<T>* si = new SearchInfo<T>(*current, develop);
                deleteQueue(open);
                deletePointers(close);
                return si;
            }

            develop++;
            for (State<T>& s : searcher->getAllPossibleStates(*(*current))) {
                if (close.find(&s) == close.end()) {
                    s.setParent(*current);
                    open.push(new State<T>(s));
                }
            }
        }
        deleteQueue(open);
        deletePointers(close);
        return new SearchInfo<T>(nullptr, develop);
    }
};

#endif
