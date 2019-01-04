#ifndef MILESTONE_2_SEARCHABLE_H
#define MILESTONE_2_SEARCHABLE_H

#include <list>
#include "state.h"

template <class T>
class Searchable {
public:
    virtual State<T> getInitialState() = 0;
    virtual State<T> getGoalState() = 0;
    virtual std::list<State<T>> getAllPossibleStates(State<T> s) = 0;
    virtual ~Searchable() {};
};
#endif
