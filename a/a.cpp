#include "lib.h"

using namespace std;

int main() {
    string pattern, text;
    cin >> pattern >> text;
    vector<int> res;
    vector<int> res = *find_substrings(pattern, text);
    for (int x : res) {
        cout << x << space_symbol;
    }
    return 0;
}
