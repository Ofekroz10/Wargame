#include "Paramedic.hpp"
#include "Board.hpp"

void Paramedic::action(vector<vector<Soldier *>> &board, pair<int, int> location) {
    vector<Soldier *> to_heal = WarGame::Board::getMySoldiers(board, location, player_num);
    for (int i = 0; i < to_heal.size(); i++) {
        to_heal[i]->hp = to_heal[i]->getInitHp();
    }
}
const uint Paramedic::getInitHp() const {
    return INIT_HP;
}