#ifndef MILESTONE_2_STATE_H
#define MILESTONE_2_STATE_H

template <class T>
class State {
protected:
    T state;  // the state we represent
    double cost;  // the cost to reach that state
    State<T>* cameFrom;  // the State we came from (setter)

public:
    // constructor
    explicit State(T state) {
        this->state = state;
        this->cameFrom = nullptr;
    }

    State() {
        this->cameFrom = nullptr;
    }

    ~State() { //delete cameFrom;
         }


    /*State(const State<T>* s) {
        this->state = s->state;
        this->cost = s->cost;
        this->cameFrom = s->cameFrom;
    }*/
    // copy constructor
    /*State(const State<T>& s) {
        this->state = s.state;
        this->cost = s.cost;
        this->cameFrom = s.cameFrom;
    }*/

    bool operator==(const State<T>& s) const { return this->state == s.state; }
    bool operator<(const State<T>& s) const { return this->state < s.state; }
    void setParent (State<T>* parent) { this->cameFrom = parent; }
    void setCost (double cost) { this->cost = cost; }
    double getCost () const { return this->cost; }
    State<T>* getParent () const { return this->cameFrom; }
    T getValue () const { return this->state; }
};

#endif
