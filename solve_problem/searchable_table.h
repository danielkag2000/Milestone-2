#ifndef MILESTONE_2_SEARCHABLE_TABLE_H
#define MILESTONE_2_SEARCHABLE_TABLE_H

#include <vector>
#include <string>
#include "searchable.h"
#include "state.h"
#include <typeinfo>
#include <sstream>

using namespace std;

typedef pair<int, int> pInt;

/**
 * a problem of search in a table
 */
class SearchableTable : public Searchable<pInt> {
    int size;
    vector<vector<int>> table;
    State<pInt> start;
    State<pInt> end;
    string detail;

public:

    SearchableTable(vector<vector<int>> table, pInt startPoint, pInt endPoint) {
        this->table = table;
        this->size = table.size();
        this->start = State<pInt>(startPoint);
        this->start.setCost(table[startPoint.first][startPoint.second]);
        this->end = State<pInt>(endPoint);

        stringstream ss;
        ss << table.size() << ',' << table[0].size()
            << '|' << startPoint.first << ',' << startPoint.second
            << '|' << endPoint.first << ',' << endPoint.second
            << '|';

        for (int i = 0; i < table.size(); ++i) {
            for (int j = 0; j < table[0].size(); ++j) {
                ss << table[i][j] << ',';
            }
        }

        this->detail = ss.str();
    }

    virtual State<pInt> getInitialState() {
        return start;
    }

    virtual State<pInt> getGoalState() {
        return end;
    }

    virtual list<State<pInt>> getAllPossibleStates(const State<pInt>& s);

    virtual bool operator==(const Searchable<pInt>& toCompare) {
        const SearchableTable* st = dynamic_cast<const SearchableTable*>(&toCompare);
        if (st == nullptr) {
            return false;
        }

        return this->detail == st->detail;
    };

    size_t hash() {
        ::hash<string> hasher;
        return hasher(detail);
    }

    virtual string toString() {
        return detail;
    }
};

#endif
