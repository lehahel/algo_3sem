#include "lib.h"

std::shared_ptr<std::vector<int>> calculate_z_function(const std::string& s) {
    int n = s.length();
    std::shared_ptr<std::vector<int>> res = std::make_shared<std::vector<int>>(n);
    int left = 0, right = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= right) {
            (*res)[i] = std::min(right - i + 1, (*res)[i - left]);
        }
        while (i + (*res)[i] < n && s[(*res)[i]] == s[i + (*res)[i]]) {
            ++(*res)[i];
        }
        if (i + (*res)[i] - 1 > right) {
            left = i;
            right = i + (*res)[i] - 1;
        }
    }
    return res;
}

std::shared_ptr<std::vector<int>> find_substrings(const std::string& pattern, const std::string& text) {
    int n = text.length(), m = pattern.length();
    std::shared_ptr<std::vector<int>> res = std::make_shared<std::vector<int>>();
    std::vector<int> zfunc = *calculate_z_function(pattern + union_symbol + text);
    for (int i = m + 1; i <= n + 1; ++i) {
        if (zfunc[i] == m) {
            (*res).emplace_back(i - m - 1);
        }
    }
    return res;
}
