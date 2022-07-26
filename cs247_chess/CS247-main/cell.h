//
// Created by work on 2022-07-25.
//

#ifndef CS247_CHESS_CELL_H
#define CS247_CHESS_CELL_H

#include <memory>
#include <utility>

class Piece;

class Cell {
    std::pair<int, int> coords;
    std::shared_ptr<Piece> piece;
public:
    Cell(std::pair<int, int>);
    void addPiece(std::shared_ptr<Piece>);
    std::shared_ptr<Piece> clear();

    bool hasPiece() const;
    char getChar() const;
    std::pair<int, int> getCoords() const;

    friend class Board;
};


#endif //CS247_CHESS_CELL_H
