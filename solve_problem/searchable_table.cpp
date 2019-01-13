#include "searchable_table.h"

list<State<pInt>> SearchableTable::getAllPossibleStates(const State<pInt>& s) {
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

    if (UP && table[i - 1][j] != -1) {
        State<pInt> child = State<pInt>({i - 1, j});
        //child->setParent(&s);
        child.setCost(s.getCost() + table[i - 1][j]);
        oper.push_back(child);
    }

    if (DOWN && table[i + 1][j] != -1) {
        State<pInt> child = State<pInt>({i + 1, j});
        child.setCost(s.getCost() + table[i + 1][j]);
        //child->setParent(&s);
        oper.push_back(child);
    }

    if (LEFT && table[i][j - 1] != -1) {
        State<pInt> child = State<pInt>({i, j - 1});
        child.setCost(s.getCost() + table[i][j - 1]);
        //child->setParent(&s);
        oper.push_back(child);
    }

    if (RIGHT && table[i][j + 1] != -1) {
        State<pInt> child = State<pInt>({i, j + 1});
        child.setCost(s.getCost() + table[i][j + 1]);
        //child->setParent(&s);
        oper.push_back(child);
    }
    return oper;
}