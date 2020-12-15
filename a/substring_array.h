#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

class SubstringArray {
public:
    SubstringArray(const std::string& pattern, const std::string& text);
    size_t operator[](const int pos) const;
    size_t size() const;

private:
    void find_substrings(const std::string& pattern, const std::string& text);
    void calculate_z_function(const std::string& s);
    std::vector<size_t> z_function;
    std::vector<size_t> substrings;
};

const std::string UNION_SYMBOL = "#";
const std::string SPACE_SYMBOL = " ";
