#ifndef MILESTONE_2_SEARCHABLE_TABLE_H
#define MILESTONE_2_SEARCHABLE_TABLE_H

#include <vector>
#include "searchable.h"
#include "state.h"

using namespace std;

typedef pair<int, int> pInt;

class SearchableTable : public Searchable<pInt> {
    int size;
    vector<vector<int>> table;
    State<pInt> start;
    State<pInt> end;

public:

    SearchableTable(vector<vector<int>> table, pInt startPoint, pInt endPoint) {
        this->table = table;
        this->size = table.size();
        this->start = State<pInt>(startPoint);
        this->start.setCost(table[startPoint.first][startPoint.second]);
        this->end = State<pInt>(endPoint);
    }

    State<pInt> getInitialState() {
        return start;
    }

    State<pInt> getGoalState() {
        return end;
    }

    virtual list<State<pInt>> getAllPossibleStates(const State<pInt>& s);
};

#endif
