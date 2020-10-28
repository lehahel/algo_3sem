#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int CHAR_CAPACITY = 127;
const std::string SPECIAL_SYMBOL = "$";
const std::string SPACE = " ";

class PrefixCountingSuffArr {
public:
    PrefixCountingSuffArr(const std::string& s);
    int find_substrings_num() const;

private:
    void init(const std::string& str);
    void build();
    void calculate_lcp();

    int class_num;
    std::vector<int> cnt;
    std::vector<int> arr;
    std::vector<int> classes;
    std::vector<int> classes_tmp;
    std::vector<int> arr_tmp;

    std::vector<std::vector<int>> step_classes;
    std::vector<int> lcp;
};