#pragma once
#include <vector>

enum class CGamePlayer { TERMINATOR, ESCAPEE };

struct CGameState {
    size_t terminator_pos;
    size_t escapee_pos;
    CGamePlayer turn;
};
