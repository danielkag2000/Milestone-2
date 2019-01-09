//
// Created by Daniel on 1/9/2019.
//

#ifndef MILESTONE_2_TEST_H
#define MILESTONE_2_TEST_H

#include <vector>
#include "solve_problem/searchable.h"
#include "solve_problem/state.h"

using namespace std;

typedef pair<int, int> pInt;

class TableGraph : public Searchable<pInt> {
    int size;
    vector<vector<int>> table;

public:

    TableGraph(vector<vector<int>> table) {
        this->table = table;
        this->size = table.size();
    }

    State<pInt> getInitialState() {
        return State<pInt>({size - 1, size - 1});
    }

    State<pInt> getGoalState() {
        return State<pInt>({size - 1, size - 1});
    }

    virtual list<State<pInt>> getAllPossibleStates(const State<pInt>& s) {
        bool UP, DOWN, LEFT, RIGHT;

        int i = s.getValue().first;
        int j = s.getValue().second;

        DOWN = i == size - 1 ? false : true;
        RIGHT = j == size - 1 ? false : true;
        UP = i == 0 ? false : true;
        LEFT = j == 0 ? false : true;

        list<State<pInt>> oper;

        if (UP && table[i][j] != -1) {
            State<pInt> child = State<pInt>({i - 1, j});
            //child->setParent(&s);
            oper.push_back(child);
        }

        if (DOWN && table[i + 1][j] != -1) {
            State<pInt> child = State<pInt>({i + 1, j});
            //child->setParent(&s);
            oper.push_back(child);
        }

        if (LEFT && table[i][j - 1] != -1) {
            State<pInt> child = State<pInt>({i, j - 1});
            //child->setParent(&s);
            oper.push_back(child);
        }

        if (RIGHT && table[i][j + 1] != -1) {
            State<pInt> child = State<pInt>({i, j + 1});
            //child->setParent(&s);
            oper.push_back(child);
        }
        return oper;
    }
};


#endif //MILESTONE_2_TEST_H
