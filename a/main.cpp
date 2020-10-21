#include "substring_array.h"

int main() {
    std::string pattern, text;
    std::cin >> pattern >> text;
    SubstringArray arr(pattern, text);
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << SPACE_SYMBOL;
    }
    return 0;

}
