//
// Created by work on 2022-07-26.
//

#ifndef CS247_CHESS_GAME_H
#define CS247_CHESS_GAME_H

#include <vector>
#include <memory>
#include <unordered_map>

#include "board.h"
#include "player.h"

class Game {
    Board board;
    std::unordered_map<bool, std::shared_ptr<Player>> players;

    void addPlayer(bool);
public:
    Game(Board);
    void addPlayers();
    void run();
};


#endif //CS247_CHESS_GAME_H
