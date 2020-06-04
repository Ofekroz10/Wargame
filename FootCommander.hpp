#pragma once
#include "FootSoldier.hpp"
class FootCommander : public FootSoldier {
private:
    static const int INIT_HP = 150;

public:
    FootCommander(){};
    FootCommander(uint num) {
        player_num = num;
        type = FOOT_COMMANDER;
        hp = INIT_HP;
        damage = 20;
    };
    ~FootCommander(){};
    void action(vector<vector<Soldier *>> &board, pair<int, int> location);
    const uint getInitHp() const;
};