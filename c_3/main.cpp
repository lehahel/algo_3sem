#include <iostream>
#include "cruelgame.h"

const std::string MUELLER = "Mueller";
const std::string SCHTIRLITZ = "Schtirlitz";

int main() {
    int n;
    std::cin >> n;
    if (n == 2) {
        std::cout << SCHTIRLITZ << std::endl;
        std::cout << "1\n2" << std::endl;
        return 0;
    }
    std::set<int> shots = CCruelGame::get_shots(n);
    if (shots.empty()) {
        std::cout << MUELLER << std::endl;
    } else {
        std::cout << SCHTIRLITZ << std::endl;
        for (int shot : shots) {
            std::cout << shot << std::endl;
        }
    }
    return 0;
}
