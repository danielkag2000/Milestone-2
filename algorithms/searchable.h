#ifndef MILESTONE_2_SEARCHABLE_H
#define MILESTONE_2_SEARCHABLE_H

#include <list>
#include "state.h"

template <class T>
class Searchable {
public:
    virtual T getInitialState() = 0;
    virtual T getGoalState() = 0;
    virtual std::list<T> getAllPossibleStates(T s) = 0;
    virtual ~Searchable() {};
};
#endif
