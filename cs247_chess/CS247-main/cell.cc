//
// Created by work on 2022-07-25.
//

#include "cell.h"
#include "piece.h"

#include <memory>

using namespace std;

Cell::Cell(std::pair<int, int> coords): coords{coords}, piece{nullptr} {}

void Cell::addPiece(shared_ptr<Piece> p) {
    piece = p;
    piece->cell = this;
}

shared_ptr<Piece> Cell::clear() {
    shared_ptr<Piece> output = piece;
    if (hasPiece()) {
        piece->cell = nullptr;
        piece = nullptr;
    }
    return output;
}

bool Cell::hasPiece() const {
    return piece != nullptr;
}

char Cell::getChar() const {
    return hasPiece() ? piece->getChar() : '_';
}

pair<int, int> Cell::getCoords() const { return coords; }
