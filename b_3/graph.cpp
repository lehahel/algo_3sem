#include "graph.h"

CGameGraph::CGameGraph(size_t size)
    : graph_terminator (),
      graph_escapee    (),
      used_terminator  (),
      used_escapee     (),
      degree_terminator(),
      degree_escapee   () {
    for (size_t i = 0; i < size; ++i) {
        graph_terminator.emplace_back (size);
        graph_escapee.emplace_back    (size);
        used_terminator.emplace_back  (size, false);
        used_escapee.emplace_back     (size, false);
        degree_terminator.emplace_back(size, 0);
        degree_escapee.emplace_back   (size, 0);
    }
}


std::vector<std::vector<std::vector<CGameState>>> &CGameGraph::operator[](CGamePlayer turn) {
    if (turn == CGamePlayer::TERMINATOR) {
        return graph_terminator;
    }
    return graph_escapee;
}

std::vector<std::vector<bool>> &CGameGraph::used(CGamePlayer turn) {
    if (turn == CGamePlayer::TERMINATOR) {
        return used_terminator;
    }
    return used_escapee;
}

std::vector<std::vector<size_t>> &CGameGraph::degree(CGamePlayer turn) {
    if (turn == CGamePlayer::TERMINATOR) {
        return degree_terminator;
    }
    return degree_escapee;
}
