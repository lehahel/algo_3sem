#include "PalyndromCounter.h"

int main() {
    std::string text;
    std::cin >> text;
    std::cout << PalyndromCounter().count(text) << std::endl;
    return 0;
}