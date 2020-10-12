#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

std::shared_ptr<std::vector<int>> calculate_z_function(const std::string& s);
std::shared_ptr<std::vector<int>> find_substrings(const std::string& pattern, const std::string& text);

const std::string union_symbol = "#";
const std::string space_symbol = " ";