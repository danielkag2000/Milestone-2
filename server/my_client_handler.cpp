#include "my_client_handler.h"

using namespace server_side;

vector<int> split(const char splitBy, const string str);
vector<pInt> from_list_to_vector (list<pInt> l);
string convert_word_path_to_string(vector<string> path);
vector<string> convert_path_to_words(list<pInt> path_list);

constexpr int minDFSSize = 35 * 35;
constexpr int maxDFSSize = 45 * 45;

inline bool outDFSRange(int x) {
    return minDFSSize >= x || maxDFSSize <= x;
}

void MyClientHandler::handleClient(istream& is, ostream& os) {
    string line;

    getline(is, line);
    vector<vector<int>> table;
    while (line != "end") {
        table.push_back(split(',', line));
        getline(is, line);
    }

    vector<int> pointEnd = table.back();
    table.pop_back();
    vector<int> pointStart = table.back();
    table.pop_back();

    if (table.empty()) {
        os << endl;
        return;
    }

    SearchableTable* st = new SearchableTable(table, make_pair(pointStart[0], pointStart[1]),
            make_pair(pointEnd[0], pointEnd[1]));

    size_t size = table.size() * table[0].size();

    string sol(findSolution(st, size));
    os << sol << endl;

    delete st;
}

string MyClientHandler::findSolution(SearchableTable* table, size_t size) {
    string tableString(table->toString());

    if (cm->solutionExists(&tableString)) {
        return *cm->getSolution(&tableString);
    }
    else {
        // create solution
        string str;
        if (outDFSRange(size)) {
            SearchInfo<pInt>* s = this->solverHolder.getSolver("BestFirstSearch")->solve(table);
            str = convert_word_path_to_string(convert_path_to_words(s->getPath()));
            delete s;

        } else {
            SearchInfo<pInt>* s = this->solverHolder.getSolver("DFS")->solve(table);
            str = convert_word_path_to_string(convert_path_to_words(s->getPath()));
            delete s;
        }

        // save solution
        cm->saveSolution(new string(tableString), new string(str));

        return str;
    }
}

vector<int> split(const char splitBy, const string str) {
    vector<int> split_line;
    string string1 = "";
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != splitBy) {
            string1 += str[i];

        } else {
            split_line.push_back(stoi(string1));
            string1 = "";
        }
    }

    split_line.push_back(stoi(string1));

    return split_line;
}

vector<string> convert_path_to_words(list<pInt> path_list) {
    vector<pInt> path = from_list_to_vector(path_list);
    vector<string> word_path;

    for (int i = 1; i < path.size(); ++i) {
        if (path[i].first - path[i - 1].first > 0) {
            word_path.push_back("Down");

        } else if (path[i].first - path[i - 1].first < 0) {
            word_path.push_back("Up");

        } else if (path[i].second - path[i - 1].second > 0) {
            word_path.push_back("Right");

        } else if (path[i].second - path[i - 1].second < 0) {
            word_path.push_back("Left");
        }
    }
    return word_path;
}

string convert_word_path_to_string(vector<string> path) {
    string str = "";

    for (int i = 0; i < path.size(); ++i) {
        str += path[i];

        if (i != path.size() - 1) {
            str += ",";
        }
    }
    return str;
}

vector<pInt> from_list_to_vector (list<pInt> l) {
    vector<pInt> vec;

    for (pInt p : l) {
        vec.push_back(p);
    }
    return vec;
}