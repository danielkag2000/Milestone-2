#ifndef MILESTONE_2_STATE_FOR_TEST_H
#define MILESTONE_2_STATE_FOR_TEST_H

#include <list>
#include <vector>
#include "../solve_problem/searchable.h"
#include "../solve_problem/state.h"

using namespace std;

/*class runTable : public State<pair<int, int>> {


public:
    runTable(int i, int j) : State<pair<int, int>>({i,j}) {}

    int getI() {return this->state.first;}
    int getJ() {return this->state.second;}
};


class tableGraph : public Searchable<runTable> {
    int size;
    vector<vector<int>> table;

public:

    tableGraph(vector<vector<int>> table) {
        this->table = table;
        this->size = table.size();
    }

    runTable getInitialState() {
        return runTable(0, 0);
    }

    runTable getGoalState() {
        return runTable(size - 1, size - 1);
    }

    virtual list<runTable*> getAllPossibleStates(runTable* s) {
        bool UP, DOWN, LEFT, RIGHT;

        DOWN = s->getI() == size - 1 ? false : true;
        RIGHT = s->getJ() == size - 1 ? false : true;
        UP = s->getI() == 0 ? false : true;
        LEFT = s->getJ() == 0 ? false : true;

        list<runTable*> oper;

        if (UP && table[s->getI() - 1][s->getJ()] != -1) {
            runTable* child = new runTable(s->getI() - 1, s->getJ());
            //child->setParent(&s);
            oper.push_back(child);
        }

        if (DOWN && table[s->getI() + 1][s->getJ()] != -1) {
            runTable* child = new runTable(s->getI() + 1, s->getJ());
            //child->setParent(&s);
            oper.push_back(child);
        }

        if (LEFT && table[s->getI()][s->getJ() - 1] != -1) {
            runTable* child = new runTable(s->getI(), s->getJ() - 1);
            //child->setParent(&s);
            oper.push_back(child);
        }

        if (RIGHT && table[s->getI()][s->getJ() + 1] != -1) {
            runTable* child = new runTable(s->getI(), s->getJ() + 1);
            //child->setParent(&s);
            oper.push_back(child);
        }
        return oper;
    }
};
*/
#endif //MILESTONE_2_STATE_FOR_TEST_H
