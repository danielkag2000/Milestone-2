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
    State<pInt> start;
    State<pInt> end;

public:

    TableGraph(vector<vector<int>>& table) : table(table) {
        //this->table = table;
        this->size = table.size();
        this->start = State<pInt>(make_pair(0, 0));
        this->start.setCost(table[0][0]);
        this->end = State<pInt>(make_pair(size - 1, size - 1));
    }

    State<pInt> getInitialState() {
        return start;
    }

    State<pInt> getGoalState() {
        return end;
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

        if (table[i][j] == -1) {
            return oper;
        }

        if (DOWN && table[i + 1][j] != -1) {
            State<pInt> child = State<pInt>({i + 1, j});
            child.setCost(s.getCost() + table[i + 1][j]);
            //child->setParent(&s);
            oper.push_back(child);
        }

        if (RIGHT && table[i][j + 1] != -1) {
            State<pInt> child = State<pInt>({i, j + 1});
            child.setCost(s.getCost() + table[i][j + 1]);
            //child->setParent(&s);
            oper.push_back(child);
        }

        if (LEFT && table[i][j - 1] != -1) {
            State<pInt> child = State<pInt>({i, j - 1});
            child.setCost(s.getCost() + table[i][j - 1]);
            //child->setParent(&s);
            oper.push_back(child);
        }

        if (UP && table[i - 1][j] != -1) {
            State<pInt> child = State<pInt>({i - 1, j});
            //child->setParent(&s);
            child.setCost(s.getCost() + table[i - 1][j]);
            oper.push_back(child);
        }

        return oper;
    }

    size_t hash() {
        return 0;
    }

    virtual string toString() {
        return "";
    }
};


#endif //MILESTONE_2_TEST_H
