#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include "wav.h"

int main() {
    std::string filename;
    std::cin >> filename;
    CWAV wav(filename);
    wav.compress(0.9);
    wav.write(filename);
    system("pause");
    return 0;
}