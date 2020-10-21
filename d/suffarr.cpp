#include "suffarr.h"

PrefixCountingSuffArr::PrefixCountingSuffArr(const std::string& str): cnt(CHAR_CAPACITY, 0),
                                          arr(str.length() + 1, 0),
                                          classes(str.length() + 1, 0),
                                          arr_tmp(str.length() + 1, 0),
                                          classes_tmp(str.length() + 1, 0),
                                          lcp(str.length(), 0) {

    std::string s = str;
    s.push_back('\0');

    init(s);
    build();
    calculate_lcp();
}

void PrefixCountingSuffArr::init(const std::string& s) {
    int n = s.length();
    for (int i = 0; i < n; ++i) {
        ++cnt[s[i]];
    }
    for (int i = 1; i < CHAR_CAPACITY; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < n; ++i) {
        arr[--cnt[s[i]]] = i;
    }
    classes[arr[0]] = 0;
    class_num = 1;
    for (int i = 1; i < n; ++i) {
        if (s[arr[i]] != s[arr[i - 1]]) {
            ++class_num;
        }
        classes[arr[i]] = class_num - 1;
    }
    step_classes.push_back(classes);
}

void PrefixCountingSuffArr::build() {
    int n = arr.size();
    for (int k = 0; (1 << k) < n; ++k) {
        cnt.assign(class_num, 0);
        for (int i = 0; i < n; ++i) {
            arr_tmp[i] = arr[i] - (1 << k);
            if (arr_tmp[i] < 0) {
                arr_tmp[i] += n;
            }
        }

        for (int i = 0; i < n; ++i) {
            ++cnt[classes[arr_tmp[i]]];
        }
        for (int i = 1; i < class_num; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            arr[--cnt[classes[arr_tmp[i]]]] = arr_tmp[i];
        }

        classes_tmp[arr[0]] = 0;
        class_num = 1;
        for (int i = 1; i < n; ++i) {
            int mid1 = (arr[i] + (1 << k)) % n;
            int mid2 = (arr[i - 1] + (1 << k)) % n;
            if (classes[arr[i]] != classes[arr[i - 1]] || classes[mid1] != classes[mid2]) {
                ++class_num;
            }
            classes_tmp[arr[i]] = class_num - 1;
        }
        step_classes.push_back(classes_tmp);
        classes = classes_tmp;
    }
}

void PrefixCountingSuffArr::calculate_lcp() {
    int log = step_classes.size() - 1;
    for (int i = 1; i < arr.size(); ++i) {
        int first = arr[i];
        int second = arr[i + 1];
        for (int k = log; k >= 0; --k) {
            if (step_classes[k][first % arr.size()] == step_classes[k][second % arr.size()]) {
                lcp[i - 1] += 1 << k;
                first += 1 << k;
                second += 1 << k;
            }
        }
    }
}

int PrefixCountingSuffArr::find_substrings_num() const {
    int res = 0;
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        res += n - arr[i] - 1;
    }
    for (int i = 0; i < n - 2; ++i) {
        res -= lcp[i];
    }
    return res;
}