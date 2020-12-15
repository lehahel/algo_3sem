#include "PalyndromCounter.h"

long long PalyndromCounter::count(const std::string& s) const {
    return inner_count(s, true) + inner_count(s, false);
}

long long PalyndromCounter::inner_count(const std::string& s, bool is_even) const {
    long long res = 0;
    long long left = 0, right = -1;
    long long n = s.length();
    std::vector<long long> dp(n, 0);

    long long even_diff = is_even ? 0 : 1;

    for (long long i = 0; i < n; ++i) {
        long long k = 0;
        if (i <= right) {
            k = std::min(right - i + even_diff, dp[right - i + left + even_diff]);
        }
        while (i + k + 1 - even_diff < n && i - k - 1 >= 0 && s[i + k + 1 - even_diff] == s[i - k - 1]) {
            ++k;
        }
        dp[i] = k;
        res += dp[i];
        if (i + k - even_diff > right) {
            left = i - k;
            right = i + k - even_diff;
        }
    }
    return res;
}
