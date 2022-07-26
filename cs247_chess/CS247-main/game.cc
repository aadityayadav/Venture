//
// Created by work on 2022-07-26.
//

#include "game.h"
#include "board.h"
#include "player.h"
#include "move.h"

#include <string>
#include <iostream>
#include <memory>
#include <utility>

using namespace std;

Game::Game(Board board): board{board} {}

void Game::addPlayer(bool colour) {
    bool success = false;
    string cmd;
    while (!success) {
        success = true;
        cin >> cmd;
        if (cmd == "human") {
            players[colour] = make_shared<Human>(colour);
        } else {
            success = false;
        }
    }
}

void Game::addPlayers() {
    addPlayer(true);
    addPlayer(false);
}

void Game::run() {
    bool currPlayer = board.getPlayer();
    board.printBoard();
    while (true) {
        shared_ptr<Move> move = players[currPlayer]->nextMove(board);
        if (move) {
            move->makeMove(board);
        } else {
            // TODO
        }
        currPlayer = !currPlayer;
        board.printBoard();
    }
}
