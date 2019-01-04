#ifndef MILESTONE_2_STATE_H
#define MILESTONE_2_STATE_H

template <class T>
class State {
private:
    T state;  // the state we represent
    double cost;  // the cost to reach that state
    State<T> cameFrom;  // the State we came from (setter)

public:
    // constructor
    State(T state) {
        this->state = state;
        this->cameFrom = nullptr;
    }

    // copy constructor
    State(State<T>& s) {
        this->state = s.state;
        this->cost = s.cost;
        this->cameFrom = s.cameFrom;
    }

    bool operator==(State<T> s) { return this->state == s; }
    void setParent (State<T> parent) { this->cameFrom = parent; }
    void setCost (double cost) { this->cost = cost; }
    State<T> getParent () { return this->cameFrom; }
};

#endif
