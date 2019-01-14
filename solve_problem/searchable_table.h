#ifndef MILESTONE_2_SEARCHABLE_TABLE_H
#define MILESTONE_2_SEARCHABLE_TABLE_H

#include <vector>
#include <string>
#include "searchable.h"
#include "state.h"
#include <typeinfo>

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

        this->detail = table.size() + "," + table[0].size();
        this->detail += "|";
        this->detail += startPoint.first + "," + startPoint.second;
        this->detail += "|";
        this->detail += endPoint.first + "," + endPoint.second;
        this->detail += "|";
        for (int i = 0; i < table.size(); ++i) {
            for (int j = 0; j < table[0].size(); ++j) {
                this->detail += table[i][j] + ",";
            }
        }
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
