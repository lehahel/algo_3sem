#include "graph.h"
#include "turntable.h"

enum class CGameCellType { TERMINATOR, ESCAPEE, WALL, VOID };

class CGame {
public:
    CGame() = delete;
    explicit CGame(size_t size);
    void set_cell_type(size_t row, size_t column, CGameCellType type);
    CGamePlayer find_winner();

private:
    int get_position(int x, int y) const;
    int get_x(int position) const;
    int get_y(int position) const;
    void perform_search(CGameState state);
    void perform_step(int terminator_pos, int escapee_pos, CGamePlayer player);
    bool available_cell(int row, int column) const;
    CGamePlayer other_player(CGamePlayer turn) const;
    size_t find_player(CGameCellType player) const;
    bool shoot(size_t terminator_x, size_t terminator_y,
               size_t escapee_x,    size_t escapee_y) const;
    bool shoot_one_direction(int terminator_x, int terminator_y,
                             int escapee_x,    int escapee_y, 
                             int direction_x,  int direction_y) const;

    size_t size;
    std::vector<std::vector<CGameCellType>> field;
    CGameTurnTable turns;
    CGamePlayer cur_turn;
    CGameGraph graph;
};
