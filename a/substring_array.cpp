#include "substring_array.h"

SubstringArray::SubstringArray(const std::string& pattern, const std::string& text) : 
        substrings(), z_function(pattern.length() + text.length() + 1) {

    find_substrings(pattern, text);                           
}

void SubstringArray::calculate_z_function(const std::string& s) {
    size_t size = s.length();
    int left = 0, right = 0;
    
    for (size_t i = 1; i < size; ++i) {
        if (i <= right) {
            z_function[i] = std::min(right - i + 1, z_function[i - left]);
        }
        while (i + z_function[i] < size && s[z_function[i]] == s[i + z_function[i]]) {
            ++z_function[i];
        }
        if (i + z_function[i] - 1 > right) {
            left = i;
            right = i + z_function[i] - 1;
        }
    }
}

void SubstringArray::find_substrings(const std::string& pattern, const std::string& text) {
    size_t text_sz = text.length();
    size_t pattern_sz = pattern.length();

    calculate_z_function(pattern + UNION_SYMBOL + text);
    for (size_t i = pattern_sz + 1; i <= text_sz + 1; ++i) {
        if (z_function[i] == pattern_sz) {
            substrings.emplace_back(i - pattern_sz - 1);
        }
    }
}

size_t SubstringArray::operator[] (const int pos) const {
    return substrings[pos];
}

size_t SubstringArray::size() const {
    return substrings.size();
}
