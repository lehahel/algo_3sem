#include "state.h"

const size_t FIELD_SIZE = 8;

class CGameGraph {
public:
    CGameGraph() = delete;
    explicit CGameGraph(size_t size);
    std::vector<std::vector<std::vector<CGameState>>> &operator[](CGamePlayer turn);
    std::vector<std::vector<bool>> &used(CGamePlayer turn);
    std::vector<std::vector<size_t>> &degree(CGamePlayer turn);

private:
    std::vector<std::vector<std::vector<CGameState>>> graph_terminator;
    std::vector<std::vector<std::vector<CGameState>>> graph_escapee;

    std::vector<std::vector<bool>> used_terminator;
    std::vector<std::vector<bool>> used_escapee;

    std::vector<std::vector<size_t>> degree_terminator;
    std::vector<std::vector<size_t>> degree_escapee;
};
