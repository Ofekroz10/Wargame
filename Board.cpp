#include "Board.hpp"
using namespace std;

namespace WarGame {
Soldier *&Board::operator[](pair<int, int> location) {
    if (location.first >= board.size() || location.second >= board[location.first].size()) {
        throw invalid_argument("You cannot set soldier outside the board size");
    }
    return board[location.first][location.second];
}
Soldier *Board::operator[](pair<int, int> location) const {
    if (location.first >= board.size() || location.second >= board[location.first].size()) {
        throw invalid_argument("You cannot set soldier the board size");
    }
    return board[location.first][location.second];
}
void Board::move(uint player_number, pair<int, int> source, MoveDIR direction) {
    if (source.first >= board.size() || source.second >= board[0].size()) {
        throw invalid_argument("You cannot move outside the board size");
    }
    Soldier *soldier = board[source.first][source.second];
    if (soldier == nullptr) {
        throw invalid_argument("soldier not found on this source");
    }
    if (soldier->getPlayerNum() != player_number) {
        throw invalid_argument("this is not your soldier");
    }
    pair<int, int> target = source;
    switch (direction) {
    case MoveDIR::Up:
        target.first = source.first + 1;
        break;
    case MoveDIR::Down:
        target.first = source.first - 1;
        break;
    case MoveDIR::Left:
        target.second = source.second - 1;
        break;
    case MoveDIR::Right:
        target.second = source.second + 1;
        break;

    default:
        break;
    }
    if (target.first >= board.size() || target.second >= board[target.first].size()) {
        throw invalid_argument("You cannot move outside the board size");
    }
    if (board[target.first][target.second] != nullptr) {
        throw invalid_argument("There is already a Soldier in target location!");
    }

    board[target.first][target.second] = soldier;
    board[source.first][source.second] = nullptr;
    soldier->action(board, target);
}
bool Board::has_soldiers(uint player_number) const {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != nullptr) {
                if (board[i][j]->getPlayerNum() == player_number) {
                    return true;
                }
            }
        }
    }
    return false;
}

pair<Soldier *, pair<int, int>> Board::getClosestEnemy(vector<vector<Soldier *>> &board, pair<int, int> source, uint enemy_player_num) {
    Soldier *closest_soldier = nullptr;
    pair<int, int> location = {-1, -1};
    double min_distance = numeric_limits<double>::max();
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            Soldier *curr_soldier = board[i][j];
            if (curr_soldier != nullptr) {
                if (curr_soldier->getPlayerNum() == enemy_player_num) {
                    double d = sqrt(pow(source.first - source.second, 2) +
                                    pow(i - j, 2) * 1.0);
                    if (d < min_distance) {
                        min_distance = d;
                        closest_soldier = curr_soldier;
                        location = {i, j};
                    }
                }
            }
        }
    }
    return {closest_soldier, location};
}
pair<Soldier *, pair<int, int>> Board::getStrongestEnemy(vector<vector<Soldier *>> &board, pair<int, int> source, uint enemy_player_num) {
    Soldier *strongest_soldier = nullptr;
    pair<int, int> location = {-1, -1};
    int max_hp = numeric_limits<double>::min();
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            Soldier *curr_soldier = board[i][j];
            if (curr_soldier != nullptr) {
                if (curr_soldier->getPlayerNum() == enemy_player_num && curr_soldier->getHp() > max_hp) {
                    max_hp = curr_soldier->getHp();
                    strongest_soldier = curr_soldier;
                    location = {i, j};
                }
            }
        }
    }
    return {strongest_soldier, location};
}
vector<Soldier *> Board::getMySoldiers(vector<vector<Soldier *>> &board, pair<int, int> source, uint player_num) {
    vector<Soldier *> soldiers;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            Soldier *curr_soldier = board[i][j];
            if (curr_soldier != nullptr) {
                if (curr_soldier->getPlayerNum() == player_num) {
                    if ((source.first + 1 == i && source.second == j) || (source.first - 1 == i && source.second == j) || (source.first == i && source.second + 1 == j) || (source.first == i && source.second - 1 == j))
                        soldiers.push_back(curr_soldier);
                }
            }
        }
    }
    return soldiers;
}
vector<pair<Soldier *, pair<int, int>>> Board::getCommanderSodliers(vector<vector<Soldier *>> &board, Type type, uint player_num) {
    vector<pair<Soldier *, pair<int, int>>> soldiers;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != nullptr) {
                if (board[i][j]->getPlayerNum() == player_num && board[i][j]->getType() == type) {
                    pair<Soldier *, pair<int, int>> soldier = {board[i][j], {i, j}};
                    soldiers.push_back(soldier);
                }
            }
        }
    }
    return soldiers;
}
} // namespace WarGame