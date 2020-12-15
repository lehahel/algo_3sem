#include <iostream>

#include "game.h"

CGameCellType get_type(char ctype) {
    if (ctype == '1') {
        return CGameCellType::WALL;
    } else if (ctype == '2') {
        return CGameCellType::ESCAPEE;
    } else if (ctype == '3') {
        return CGameCellType::TERMINATOR;
    } else {
        return CGameCellType::VOID;
    }
}

int main() {
    char type;
    CGame game(FIELD_SIZE);
    for (size_t i = 0; i < FIELD_SIZE; ++i) {
        for (size_t j = 0; j < FIELD_SIZE; ++j) {
            std::cin >> type;
            game.set_cell_type(i, j, get_type(type));
        }
    }
    if (game.find_winner() == CGamePlayer::ESCAPEE) {
        std::cout << 1 << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }
    return 0;
}
