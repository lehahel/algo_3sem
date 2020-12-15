#pragma once

#include "state.h"

enum class CGameTurnState { WIN, LOSE, UNDEFINED };

class CGameTurnTable {
public:
    CGameTurnTable() = default;
    explicit CGameTurnTable(size_t size);
    std::vector<std::vector<CGameTurnState>> &operator[](CGamePlayer turn);

private:
    std::vector<std::vector<CGameTurnState>> states_terminator;
    std::vector<std::vector<CGameTurnState>> states_escapee;
};
