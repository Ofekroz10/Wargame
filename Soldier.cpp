#include "Soldier.hpp"

uint Soldier::getEnemyPlayerNum() {
    if (player_num == 1)
        return 2;
    else
        return 1;
}