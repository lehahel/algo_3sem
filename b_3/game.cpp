#include "game.h"

CGame::CGame(size_t size) 
      : size(size), cur_turn(CGamePlayer::ESCAPEE), 
        turns(size * size), graph(size * size) {
    for (size_t i = 0; i < size; ++i) {
        field.emplace_back(size, CGameCellType::VOID);
    }
}

void CGame::set_cell_type(size_t row, size_t column, CGameCellType type) {
    field[row][column] = type;
}

bool CGame::available_cell(int row, int column) const {
    return row >= 0 && row < size &&
           column >= 0 && column < size &&
           field[row][column] != CGameCellType::WALL;
}

int CGame::get_position(int x, int y) const {
    return x * size + y;
}

int CGame::get_x(int position) const {
    return position / size;
}

int CGame::get_y(int position) const {
    return position % size;
}

CGamePlayer CGame::other_player(CGamePlayer turn) const {
    return turn == CGamePlayer::TERMINATOR ?
                   CGamePlayer::ESCAPEE :
                   CGamePlayer::TERMINATOR;
}

size_t CGame::find_player(CGameCellType player) const {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (field[i][j] == player) {
                return i * size + j;
            }
        }
    }
    return size * size;
}

void CGame::perform_search(CGameState state) {
    size_t terminator_pos = state.terminator_pos;
    size_t escapee_pos = state.escapee_pos;
    CGamePlayer turn = state.turn;
    
    auto &cur_graph = graph[turn];
    auto &cur_used = graph.used(turn);
    
    graph.used(turn)[terminator_pos][escapee_pos] = true;

    for (auto it = cur_graph[terminator_pos][escapee_pos].begin(); it != cur_graph[terminator_pos][escapee_pos].end(); ++it) {
        if (!graph.used(it->turn)[it->terminator_pos][it->escapee_pos]) {
            if (turns[turn][terminator_pos][escapee_pos] == CGameTurnState::LOSE) {
                turns[it->turn][it->terminator_pos][it->escapee_pos] = CGameTurnState::WIN;
            } else if (--graph.degree(it->turn)[it->terminator_pos][it->escapee_pos] == 0) {
                turns[it->turn][it->terminator_pos][it->escapee_pos] = CGameTurnState::LOSE, it->turn;
            } else {
                continue;
            }
            perform_search(*it);
        }
    }
}

bool CGame::shoot_one_direction(int terminator_x, int terminator_y,
                                int escapee_x,    int escapee_y, 
                                int direction_x,  int direction_y) const {
    while (terminator_x >= 0 && terminator_x < size &&
           terminator_y >= 0 && terminator_y < size) {
        
        if (field[terminator_x][terminator_y] == CGameCellType::WALL) {
            return false;
        }
        if (terminator_x == escapee_x && terminator_y == escapee_y) {
            return true;
        }
        terminator_x += direction_x;
        terminator_y += direction_y;
    }
    return false;
}

bool CGame::shoot(size_t terminator_x, size_t terminator_y,
                  size_t escapee_x,    size_t escapee_y) const {
    bool res = false;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i != 0 || j != 0) {
                res |= shoot_one_direction(terminator_x, terminator_y, 
                                           escapee_x, escapee_y, i, j);
            }
        }
    }
    return res;
}

void CGame::perform_step(int terminator_pos, int escapee_pos, CGamePlayer turn) {
    int terminator_x = terminator_pos / FIELD_SIZE;
    int terminator_y = terminator_pos % FIELD_SIZE;

    int escapee_x = escapee_pos / FIELD_SIZE;
    int escapee_y = escapee_pos % FIELD_SIZE;

    if (field[terminator_x][terminator_y] == CGameCellType::WALL ||
              field[escapee_x][escapee_y] == CGameCellType::WALL) {
        return;
    }

    CGameTurnState &cur_turn = turns[turn][terminator_pos][escapee_pos];
    CGameTurnState &opposite_turn =
         turns[other_player(turn)][terminator_pos][escapee_pos];

    if (shoot(terminator_x, terminator_y, escapee_x, escapee_y)) {
        turns[CGamePlayer::TERMINATOR][terminator_pos][escapee_pos] = 
                                                 CGameTurnState::WIN;
        turns[CGamePlayer::ESCAPEE][terminator_pos][escapee_pos] = 
                                                 CGameTurnState::LOSE;
    } else if (escapee_x == size - 1) {
        turns[CGamePlayer::TERMINATOR][terminator_pos][escapee_pos] = 
                                                 CGameTurnState::LOSE;
        turns[CGamePlayer::ESCAPEE][terminator_pos][escapee_pos] = 
                                                 CGameTurnState::WIN;
    }

    if (cur_turn != CGameTurnState::UNDEFINED &&
         opposite_turn != CGameTurnState::UNDEFINED) {
        return;
    }

    CGameState state = { static_cast<size_t>(terminator_x), 
                         static_cast<size_t>(terminator_y),
                         other_player(turn) };

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            int terminator_x_tmp = terminator_x;
            int terminator_y_tmp = terminator_y;
            int escapee_x_tmp = escapee_x;
            int escapee_y_tmp = escapee_y;
            if (turn == CGamePlayer::TERMINATOR) {
                terminator_x_tmp += i;
                terminator_y_tmp += j;
                if (!available_cell(terminator_x_tmp, terminator_y_tmp)) {
                    continue;
                }
            } else {
                escapee_x_tmp += i;
                escapee_y_tmp += j;
                if (!available_cell(escapee_x_tmp, escapee_y_tmp)) {
                    continue;
                }
            }
            if (terminator_x_tmp >= 0 && terminator_y_tmp >= 0 &&
                terminator_x_tmp < size && terminator_y_tmp < size &&
                escapee_x_tmp >= 0 && escapee_y_tmp >= 0 &&
                escapee_x_tmp < size && escapee_y_tmp < size) {
                graph[other_player(turn)][terminator_x_tmp * size + 
                                          terminator_y_tmp][escapee_x_tmp * size + 
                                                            escapee_y_tmp].emplace_back(state);
            }
        }
    }
}

CGamePlayer CGame::find_winner() {
    for (size_t terminator_pos = 0; terminator_pos < size * size; ++terminator_pos) {
        for (size_t escapee_pos = 0; escapee_pos < size * size; ++escapee_pos) {
            perform_step(terminator_pos, escapee_pos, CGamePlayer::ESCAPEE);
            perform_step(terminator_pos, escapee_pos, CGamePlayer::TERMINATOR);
        }
    }

    for (size_t terminator_pos = 0; terminator_pos < size * size; ++terminator_pos) {
        for (size_t escapee_pos = 0; escapee_pos < size * size; ++escapee_pos) {
            if (turns[CGamePlayer::TERMINATOR][terminator_pos][escapee_pos] != CGameTurnState::UNDEFINED &&
                !graph.used(CGamePlayer::TERMINATOR)[terminator_pos][escapee_pos]) {
                perform_search({ terminator_pos, escapee_pos, CGamePlayer::TERMINATOR });
            }
            if (turns[CGamePlayer::ESCAPEE][terminator_pos][escapee_pos] != CGameTurnState::UNDEFINED &&
                !graph.used(CGamePlayer::ESCAPEE)[terminator_pos][escapee_pos]) {
                perform_search({ terminator_pos, escapee_pos, CGamePlayer::ESCAPEE });
            }
        }
    }
    size_t terminator_pos = find_player(CGameCellType::TERMINATOR);
    size_t escapee_pos = find_player(CGameCellType::ESCAPEE);

    if (turns[CGamePlayer::ESCAPEE][terminator_pos][escapee_pos] == CGameTurnState::WIN) {
        return CGamePlayer::ESCAPEE;
    } else {
        return CGamePlayer::TERMINATOR;
    }
}
