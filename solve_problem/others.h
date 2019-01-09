//
// Created by Daniel on 1/9/2019.
//

#ifndef MILESTONE_2_OTHERS_H
#define MILESTONE_2_OTHERS_H

#include <utility>

bool operator==(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    return p1.first == p2.first && p1.second == p2.second;
}

template <class T1, class T2>
bool operator<(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) {
    return p1.first < p2.first && p1.second < p2.second;
}

#endif //MILESTONE_2_OTHERS_H
