#include "my_client_handler.h"

vector<int> split(const char splitBy, const string str);
vector<pInt> from_list_to_vector (list<pInt> l);
string convert_word_path_to_string(vector<string> path);
vector<string> convert_path_to_words(list<pInt> path_list);

void server_side::MyClientHandler::handleClient(istream& is, ostream& os) {
    string line;

    getline(is, line);
    vector<vector<int>> table;
    while (line != "end") {
        table.push_back(split(',', line));
        getline(is, line);
    }
    getline(is, line);
    vector<int> pointStart = split(',', line);
    getline(is, line);
    vector<int> pointEnd = split(',', line);

    if (table.empty()) {
        return;
    }

    SearchableTable* st = new SearchableTable(table, make_pair(pointStart[0], pointStart[1]), make_pair(pointEnd[0], pointEnd[1]));

    int size = table.size() * table[0].size();

    string str;
    if (size <= 1225 || size >= 2025) {
        SearchInfo<pInt>* s = this->solverHolder.getSolver("BestFirstSearch")->solve(st);
        str = convert_word_path_to_string(convert_path_to_words(s->getPath()));
        delete s;

    } else { // 1225 < size < 2025
        SearchInfo<pInt>* s = this->solverHolder.getSolver("DFS")->solve(st);
        str = convert_word_path_to_string(convert_path_to_words(s->getPath()));
        delete s;
    }

    os << str << endl;

    delete st;
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