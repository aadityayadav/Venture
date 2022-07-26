//
// Created by work on 2022-07-25.
//

#ifndef CS247_CHESS_MOVE_H
#define CS247_CHESS_MOVE_H

#include <vector>
#include <string>
#include <utility>

class Change;

class Board;

class Move {
    bool colour;
    std::pair<int, int> start;
    std::pair<int, int> end;
protected:
    std::vector<std::shared_ptr<Change>> changes;
public:
    Move(bool, std::vector<std::shared_ptr<Change>>, std::pair<int, int>, std::pair<int, int>);

    void makeMove(Board &);
    void undoMove(Board &);

    std::pair<int, int> getStart() const;
    std::pair<int, int> getEnd() const;

    virtual ~Move() = default;
};

class PromotionMove: public Move {
public:
    PromotionMove(bool, std::pair<int, int>, std::pair<int, int>, char);
};

class RegularMove: public Move {
public:
    RegularMove(bool, std::pair<int, int>, std::pair<int, int>);
};

class CastleMove: public Move {
public:
    CastleMove(bool, std::pair<int, int>, std::pair<int, int>);
};

class CaptureMove: public Move {
public:
    CaptureMove(bool, std::pair<int, int>, std::pair<int, int>);
};

#endif //CS247_CHESS_MOVE_H
