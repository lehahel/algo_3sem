#include "lib.h"

void calculate_z_function(const string& s, vector<int>& res) {
    int n = s.length();
    res.resize(n, 0);
    int left = 0, right = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= right) {
            res[i] = min(right - i + 1, res[i - left]);
        }
        while (i + res[i] < n && s[res[i]] == s[i + res[i]]) {
            ++res[i];
        }
        if (i + res[i] - 1 > right) {
            left = i;
            right = i + res[i] - 1;
        }
    }
}

void find_substrings(const string& pattern, const string& text, vector<int>& res) {
    int n = text.length(), m = pattern.length();
    vector<int> zfunc;
    calculate_z_function(pattern + "#" + text, zfunc);
    for (int i = m + 1; i <= n + 1; ++i) {
        if (zfunc[i] == m) {
            res.emplace_back(i - m - 1);
        }
    }
}