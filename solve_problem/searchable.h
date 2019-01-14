#ifndef MILESTONE_2_SEARCHABLE_H
#define MILESTONE_2_SEARCHABLE_H

#include <list>
#include <functional>
#include <string>
#include "state.h"

/**
 * represent a problem of search
 * @tparam T the type of the state
 */
template <class T>
class Searchable {
public:
    virtual State<T> getInitialState() = 0;
    virtual State<T> getGoalState() = 0;
    /**
     * get all the develop states from the state (s)
     * @param s the state to develop
     * @return all possible states
     */
    virtual std::list<State<T>> getAllPossibleStates(const State<T>& s) = 0;
    virtual ~Searchable() {};
    virtual bool operator==(const Searchable<T>&) = 0;
    virtual size_t hash() = 0;
    virtual std::string toString() = 0;
};
#endif
