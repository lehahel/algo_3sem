#include "cruelgame.h"

int CCruelGame::get_mex(const std::vector<int> &nums) {
    std::set<int> nums_tmp(nums.begin(), nums.end());
    int i = 0;
    while (nums_tmp.count(i) != 0) {
        ++i;
    }
    return i;
}

std::set<int> CCruelGame::find_shots(int num, const std::vector<int> &people) {
    std::set<int> res;
    if (people[num] == 0) {
        return res;
    }
    if (people[num - 1] == 0) {
        res.insert(1);
        res.insert(num);
    }
    if (num >= 3 && people[num - 2] == 0) {
        res.insert(2);
        res.insert(num - 1);
    }
    for (int i = 3; i <= num; ++i) {
        if ((people[i - 1] ^ people[num - i]) == 0) {
            res.insert(i);
        }
    }
    return res;
}

std::set<int> CCruelGame::get_shots(int num) {
    std::vector<int> people(num + 1);
    for (int i = 1; i < 4; ++i) {
        people[i] = i - 1;
    }
    for (int i = 4; i <= num; ++i) {
        std::vector<int> cur;
        cur.emplace_back(people[i - 1]);
        cur.emplace_back(people[i - 2]);
        for (int j = 3; j <= i - 2; ++j) {
            cur.emplace_back(people[j - 1] ^ people[i - j]);
        }
        people[i] = get_mex(cur);
    }
    return find_shots(num, people);
}
