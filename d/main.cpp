#include "suffarr.h"

int main() {
    std::string s;
    std::cin >> s; 
    PrefixCountingSuffArr arr(s);
    std::cout << arr.find_substrings_num() << std::endl;
    return 0;
}