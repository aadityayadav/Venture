//
// Created by work on 2022-07-25.
//

#ifndef CS247_CHESS_BOARD_H
#define CS247_CHESS_BOARD_H

#include <vector>
#include <utility>
#include <string>

#include "cell.h"

class Piece;

class King;

class Move;

class Board {
    // members
    static int width, height;
    std::vector<std::vector<Cell>> grid;
    bool player;

    // helpers
    void initializeGrid();
    void clearGrid();
    std::shared_ptr<Piece> pieceAt(std::pair<int, int>);
    void plusPiece(std::shared_ptr<Piece>, std::pair<int, int>);
    std::shared_ptr<Piece> minusPiece(std::pair<int, int>);
    void addPiece(char, std::string);
    void removePiece(std::string);
    std::vector<std::shared_ptr<Piece>> getPieces(char, bool) const;
    std::vector<std::shared_ptr<Piece>> getPieces(char) const;
    std::vector<std::shared_ptr<Piece>> getPieces(bool) const;
    std::vector<std::shared_ptr<Piece>> getPieces() const;

    bool validateKings() const;
    bool validatePawns() const;
public:
    Board();

    void setup();


    void printBoard() const; // TODO: eventually remove this

    std::vector<std::shared_ptr<Move>> getValidMoves(bool);
    std::pair<bool, bool> checkedPlayer() const;
    bool getPlayer() const;
    bool colourAt(std::pair<int, int>) const;
    bool isFree(std::pair<int, int>) const;
    static std::pair<int, int> getXY(std::string);
    static std::string getLetters(std::pair<int, int>);
    static bool inBounds(std::pair<int, int>);
    static std::shared_ptr<Piece> getPiece(char);

    friend class Change;
    friend class AddPiece;
    friend class RemovePiece;
    friend class Shift;
};

#endif //CS247_CHESS_BOARD_H
