//
// Created by work on 2022-07-26.
//

#include "player.h"
#include "move.h"
#include "board.h"

#include <memory>
#include <iostream>

using namespace std;

Player::Player(bool colour): colour{colour} {}

std::shared_ptr<Move> Player::nextMove(Board & board) { return getNextMove(colour, board); }

Human::Human(bool colour): Player{colour} {}

std::shared_ptr <Move> Human::getNextMove(bool playerColour, Board & board) {
    string cmd;
    while (true) {
        cin >> cmd;
        if (cmd == "move") {
            string start, end;
            cin >> start >> end;
            for (auto& move: board.getValidMoves(playerColour)) {
                if (board.getXY(start) == move->getStart() && board.getXY(end) == move->getEnd()) {
                    return move;
                }
            }
            cout << "Move not found!" << endl;
        } else if (cmd == "moves") {
            for (auto& move: board.getValidMoves(playerColour)) {
                cout << board.getLetters(move->getStart()) << " " << board.getLetters(move->getEnd()) << endl;
            }
        } else if (cmd == "resign") {
            return nullptr;
        } else {
            cout << "Invalid game command!" << endl;
        }
    }
}

Computer::Computer(bool colour): Player{colour} {}

Level1Computer::Level1Computer(bool colour): Computer{colour} {}

std::shared_ptr<Move> Level1Computer::getNextMove(bool comp_colour,Board &board) {
     return board.getValidMoves(comp_colour)[rand() % board.getValidMoves(comp_colour).size()];
}


Level2Computer::Level2Computer(bool colour): Computer{colour} {
    
}

std::shared_ptr<Move> Level2Computer::getNextMove(bool colour,Board &board) {}


Level3Computer::Level3Computer(bool colour): Computer{colour} {}

std::shared_ptr<Move> Level3Computer::getNextMove(bool colour,Board &board) {}


Level4Computer::Level4Computer(bool colour): Computer{colour} {}

std::shared_ptr<Move> Level4Computer::getNextMove(bool colour,Board &board) {}
