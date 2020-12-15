#pragma once

#include <vector>
#include <set>

class CCruelGame {
public:
    static std::set<int> get_shots(int num);
private:
    static std::set<int> find_shots(int num, const std::vector<int> &people);
    static int get_mex(const std::vector<int> &nums);
};
