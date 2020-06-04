#include "FootSoldier.hpp"
#include "Board.hpp"

void FootSoldier::action(vector<vector<Soldier *>> &board, pair<int, int> location) {
    pair<Soldier *, pair<int, int>> to_attack = WarGame::Board::getClosestEnemy(board, location, getEnemyPlayerNum());
    if (to_attack.first == nullptr)
        return;
    to_attack.first->hp -= damage;
    if (to_attack.first->hp <= 0) {
        board[to_attack.second.first][to_attack.second.second] = nullptr;
        delete to_attack.first;
    }
}
const uint FootSoldier::getInitHp() const {
    return INIT_HP;
}