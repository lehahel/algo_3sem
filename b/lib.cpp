#include "lib.h"

long long calculate_odd_palyndroms(const string& s) {
    long long res = 0;
    long long left = 0, right = -1;
    long long n = s.length();
    vector<long long> dp(n, 0);
    for (long long i = 0; i < n; ++i) {
        long long k = 0;
        if (i <= right) {
            k = min(right - i, dp[right - i + left]);
        }
        while (i + k + 1 < n && i - k - 1 >= 0 && s[i + k + 1] == s[i - k - 1]) {
            ++k;
        }
        dp[i] = k;
        res += dp[i];
        if (i + k > right) {
            left = i - k;
            right = i + k;
        }
    }
    return res;
}

long long calculate_even_palyndroms(const string& s) {
    long long res = 0;
    long long left = 0, right = -1;
    long long n = s.length();
    vector<long long> dp(n, 0);
    for (long long i = 0; i < n; ++i) {
        long long k = 0;
        if (i <= right) {
            k = min(right - i + 1, dp[right - i + left + 1]);
        }
        while (i + k < n && i - k - 1 >= 0 && s[i + k] == s[i - k - 1]) {
            ++k;
        }
        dp[i] = k;
        res += dp[i];
        if (i + k - 1 > right) {
            left = i - k;
            right = i + k - 1;
        }
    }
    return res;
}

long long calculate_palyndroms(const string& s) {
    return calculate_even_palyndroms(s) + calculate_odd_palyndroms(s);
}