//
// Created by work on 2022-07-25.
//

#ifndef CS247_CHESS_PIECE_H
#define CS247_CHESS_PIECE_H

#include <utility>
#include <vector>

class Move;

class Cell;

class Board;

class Piece {
    virtual char getCharRep() const = 0;
    std::vector<std::shared_ptr<Move>> getTargetMoves(const Board &) const;
    virtual std::vector<std::pair<int, int>> getCandidateTargets(const Board &) const = 0;
protected:
    bool colour;
    Cell* cell;
    bool moved;
    std::vector<std::pair<int, int>> getLines(std::vector<std::pair<int, int>>, const Board &) const;
    std::vector<std::pair<int, int>> getLine(std::pair<int, int>, const Board &) const;
public:
    Piece(bool, Cell* cell = nullptr);

    std::vector<std::shared_ptr<Move>> getPossibleMoves(const Board &) const;
    std::vector<std::pair<int, int>> getPossibleTargets(const Board &) const;
    char getChar() const;
    bool getColour() const;
    std::pair<int, int> getCoords() const;

    virtual ~Piece() = default;

    friend Cell;
};

class Rook: public Piece {
    char getCharRep() const override;
    std::vector<std::pair<int, int>> getCandidateTargets(const Board &) const override;
public:
    Rook(bool, Cell* cell = nullptr);

    static const std::vector<std::pair<int, int>> directions;
};

class Pawn: public Piece {
    std::pair<int, int> direction;
    char getCharRep() const override;
    std::vector<std::pair<int, int>> getCandidateTargets(const Board &) const override;
public:
    Pawn(bool, Cell* cell = nullptr);
};

class Bishop: public Piece {
    char getCharRep() const override;
    std::vector<std::pair<int, int>> getCandidateTargets(const Board &) const override;
public:
    Bishop(bool, Cell* cell = nullptr);

    static const std::vector<std::pair<int, int>> directions;
};

class Knight: public Piece {
    char getCharRep() const override;
    std::vector<std::pair<int, int>> getCandidateTargets(const Board &) const override;
public:
    Knight(bool, Cell* cell = nullptr);
};

class King: public Piece {
    char getCharRep() const override;
    std::vector<std::pair<int, int>> getCandidateTargets(const Board &) const override;
public:
    King(bool, Cell* cell = nullptr);
};

class Queen: public Piece {
    char getCharRep() const override;
    std::vector<std::pair<int, int>> getCandidateTargets(const Board &) const override;
public:
    Queen(bool, Cell* cell = nullptr);

    static const std::vector<std::pair<int, int>> directions;
};

#endif //CS247_CHESS_PIECE_H
