//
// Created by work on 2022-07-26.
//

#ifndef CS247_CHESS_PLAYER_H
#define CS247_CHESS_PLAYER_H

#include <memory>

class Board;

class Move;

class Player {
    bool colour;
    virtual std::shared_ptr<Move> getNextMove(bool, Board &) = 0;
public:
    Player(bool);
    std::shared_ptr<Move> nextMove(Board &);
    virtual ~Player() = default;
};

class Human: public Player {
    std::shared_ptr<Move> getNextMove(bool, Board &);
public:
    Human(bool);
};

class Computer: public Player{
public:
    Computer(bool);
};

class Level1Computer: public Computer{
    std::shared_ptr<Move> getNextMove(bool,Board &);
public: 
    Level1Computer(bool);
};

class Level2Computer: public Computer{
    std::shared_ptr<Move> getNextMove(bool,Board &);
public: 
    Level2Computer(bool);
};

class Level3Computer: public Computer{
    std::shared_ptr<Move> getNextMove(bool,Board &);
public: 
    Level3Computer(bool);
};

class Level4Computer: public Computer{
    std::shared_ptr<Move> getNextMove(bool,Board &);
public: 
    Level4Computer(bool);
};


#endif //CS247_CHESS_PLAYER_H
