//
// Created by work on 2022-07-25.
//

#include "change.h"
#include "board.h"

#include <memory>
#include <utility>

using namespace std;

// Change
Change::Change(pair<int, int> start, pair<int, int> end, shared_ptr<Piece> piece): start{start}, end{end}, piece{piece} {}

pair<int, int> Change::getStart() { return start; }

pair<int, int> Change::getEnd() { return end; }

shared_ptr<Piece> Change::getPiece() { return piece; }

void Change::makeChange(Board& b) {
    applyChange(b);
}

void Change::undoChange(Board &b) {
    removeChange(b);
}

Change::~Change() {}

// Shift
Shift::Shift(pair<int, int> start, pair<int, int> end): Change{start, end} {}

void Shift::applyChange(Board& b) {
    b.plusPiece(b.minusPiece(start), end);
}

void Shift::removeChange(Board &b) {
    b.plusPiece(b.minusPiece(end), start);
}

// AddPiece
AddPiece::AddPiece(std::shared_ptr<Piece> piece, pair<int, int> coords): Change{{}, coords, piece} {}

void AddPiece::applyChange(Board& b) {
    b.plusPiece(piece, end);
}

void AddPiece::removeChange(Board &b) {
    b.minusPiece(end);
}

// RemovePiece
RemovePiece::RemovePiece(std::pair<int, int> coords): Change{coords, {}} {}

void RemovePiece::applyChange(Board& b) {
    piece = b.pieceAt(start);
    b.minusPiece(start);
}

void RemovePiece::removeChange(Board &b) {
    b.plusPiece(piece, start);
}
