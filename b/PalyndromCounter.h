#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class PalyndromCounter {
public:
    long long count(const std::string& s) const;
private:
    long long inner_count(const std::string& s, bool is_even) const;
};
