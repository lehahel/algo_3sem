#include "turntable.h"

CGameTurnTable::CGameTurnTable(size_t size)
 : states_terminator(), states_escapee() {
    for (size_t i = 0; i < size; ++i) {
        states_terminator.emplace_back(size, CGameTurnState::UNDEFINED);
        states_escapee.emplace_back   (size, CGameTurnState::UNDEFINED);
    }
}

std::vector<std::vector<CGameTurnState>> &CGameTurnTable::operator[](CGamePlayer turn) {
    if (turn == CGamePlayer::TERMINATOR) {
        return states_terminator;
    } else {
        return states_escapee;
    }
}
