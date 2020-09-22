#include "lib.h"

using namespace std;

int main() {
    string pattern, text;
    cin >> pattern >> text;
    vector<int> res;
    find_substrings(pattern, text, res);
    for (int x : res) {
        cout << x << " ";
    }
    cout << endl;
    //system("pause");
    return 0;
}