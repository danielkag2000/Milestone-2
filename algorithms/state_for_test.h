#ifndef MILESTONE_2_STATE_FOR_TEST_H
#define MILESTONE_2_STATE_FOR_TEST_H

#include <list>
#include <vector>
#include "searchable.h"

using namespace std;
class runTable : public State<pair<int, int>> {
    pair<int, int> i_j;

public:
    runTable(int i, int j) {
        this->i_j = pair<int, int>(i, j);
    }

    int getI() {return i_j.first;}
    int getJ() {return i_j.second;}

    vector<vector<int>> copyArray( vector<vector<int>> t) {
        vector<vector<int>> copy;

        for (int i = 0; i < t.size(); i++) {
            for (int j = 0; j < t.size(); j++) {
                copy.push_back(t[i]);
            }
        }
        return copy;
    }
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

    virtual list<runTable> getAllPossibleStates(runTable s) {
        bool UP, DOWN, LEFT, RIGHT;

        DOWN = s.getI() == size - 1 ? false : true;
        RIGHT = s.getJ() == size - 1 ? false : true;
        UP = s.getI() == 0 ? false : true;
        LEFT = s.getJ() == 0 ? false : true;

        list<runTable> oper;

        if (UP) {
            runTable child = runTable(s.getI() - 1, s.getJ());
            child.setParent(s);
            oper.push_back(child);
        }

        if (DOWN) {
            runTable child = runTable(s.getI() + 1, s.getJ());
            child.setParent(s);
            oper.push_back(child);
        }

        if (LEFT) {
            runTable child = runTable(s.getI(), s.getJ() - 1);
            child.setParent(s);
            oper.push_back(child);
        }

        if (RIGHT) {
            runTable child = runTable(s.getI(), s.getJ() + 1);
            child.setParent(s);
            oper.push_back(child);
        }
        return oper;
    }
};

#endif //MILESTONE_2_STATE_FOR_TEST_H
