//
// Created by work on 2022-07-25.
//

#include "piece.h"
#include "board.h"
#include "cell.h"
#include "move.h"

#include <utility>
#include <vector>
#include <iostream>

using namespace std;

pair<int, int> operator+(const pair<int,int> &a, const pair<int,int> &b) {
    return {a.first + b.first,a.second + b.second};
}


vector <shared_ptr<Move>> Piece::getTargetMoves(const Board & board) const {
    vector<shared_ptr<Move>> possibleMoves;
    for (auto& target: getPossibleTargets(board)) {
        shared_ptr<Move> move;
        if (board.isFree(target)) {
            move = make_shared<RegularMove>(colour, getCoords(), target);
        } else {
            move = make_shared<CaptureMove>(colour, getCoords(), target);
        }
        possibleMoves.push_back(move);
    }
    return possibleMoves;
}

vector<shared_ptr<Move>> Piece::getPossibleMoves(const Board & board) const {
    // TODO: Special Moves
    return getTargetMoves(board);
}

vector<pair<int, int>> Piece::getPossibleTargets(const Board & board) const {
    vector<pair<int, int>> possibleTargets;
    for (auto target: getCandidateTargets(board)) {
        if (board.inBounds(target) && (board.isFree(target) || board.colourAt(target) != colour)) possibleTargets.push_back(target);
    }
    return possibleTargets;
}

vector<pair<int, int>> Piece::getLines(vector<pair<int, int>> directions, const Board& board) const {
    vector<pair<int, int>> lines;
    for (auto dir: directions) {
        vector<pair<int, int>> line = getLine(dir, board);
        lines.reserve(lines.size() + line.size());
        lines.insert(lines.end(), line.begin(), line.end());
    }
    return lines;
}

vector<pair<int, int>> Piece::getLine(pair<int, int> direction, const Board& board) const {
    vector<pair<int, int>> lineCoordinates;
    pair<int, int> targetCoordinates = getCoords() + direction;
    while (board.inBounds(targetCoordinates)) {
        lineCoordinates.push_back(targetCoordinates);
        if (!board.isFree(targetCoordinates)) break;
        targetCoordinates = targetCoordinates + direction;
    }
    return lineCoordinates;
}

Piece::Piece(bool colour, Cell* cell): colour{colour}, cell{cell}, moved{false} {}

char Piece::getChar() const { return getCharRep(); }

bool Piece::getColour() const { return colour; }

pair<int, int> Piece::getCoords() const { return cell->getCoords(); }

Rook::Rook(bool colour, Cell* cell): Piece(colour, cell) {}

char Rook::getCharRep() const {
    return colour ? 'R' : 'r';
}

vector<pair<int, int>> Rook::getCandidateTargets(const Board & board) const { return getLines(directions, board); }


const vector<pair<int, int>> Rook::directions = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}
};

Pawn::Pawn(bool colour, Cell* cell): Piece(colour, cell), direction{colour ? make_pair(0, -1) : make_pair(0, 1)} {}

char Pawn::getCharRep() const {
    return colour ? 'P' : 'p';
}

vector<pair<int, int>> Pawn::getCandidateTargets(const Board & board) const {
    vector<pair<int, int>> candidates;
    pair<int, int> basic = getCoords() + direction;
    vector<pair<int, int>> captures = {
            getCoords() + make_pair(1, 0) + direction,
            getCoords() + make_pair(-1, 0) + direction
    };

    if (board.inBounds(basic) && board.isFree(basic)) {
        candidates.push_back(basic);
        pair<int, int> doubleForwards = basic + direction;
        if (!moved && board.inBounds(doubleForwards) && board.isFree(doubleForwards)) {
            candidates.push_back(doubleForwards);
        }
    }

    for (auto capture: captures) {
        if (board.inBounds(capture) && !board.isFree(capture)) {
            candidates.push_back(capture);
        }
    }

    return candidates;
}

Bishop::Bishop(bool colour, Cell* cell): Piece(colour, cell) {}

char Bishop::getCharRep() const {
    return colour ? 'B' : 'b';
}

vector<pair<int, int>> Bishop::getCandidateTargets(const Board & board) const { return getLines(directions, board); }

const vector<pair<int, int>> Bishop::directions = {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

Knight::Knight(bool colour, Cell* cell): Piece(colour, cell) {}

char Knight::getCharRep() const {
    return colour ? 'N' : 'n';
}

vector<pair<int, int>> Knight::getCandidateTargets(const Board &) const {
    pair<int, int> coords = getCoords();
    return {
            {coords.first + 2, coords.second + 1},
            {coords.first + 2, coords.second - 1},
            {coords.first - 2, coords.second + 1},
            {coords.first - 2, coords.second - 1},
            {coords.first + 1, coords.second + 2},
            {coords.first - 1, coords.second + 2},
            {coords.first + 1, coords.second - 2},
            {coords.first - 1, coords.second - 2}
    };
}

King::King(bool colour, Cell* cell): Piece(colour, cell) {}

char King::getCharRep() const {
    return colour ? 'K' : 'k';
}

vector<pair<int, int>> King::getCandidateTargets(const Board &) const {
    vector<int> changes = {-1, 0, 1};
    vector<pair<int, int>> candidates;
    pair<int, int> coords = getCoords();

    for (auto c1: changes) {
        for (auto c2: changes) {
            if (!(c1 == 0 && c2 == 0)) {
                candidates.emplace_back(coords.first + c1, coords.second + c2);
            }
        }
    }
    return candidates;
}


Queen::Queen(bool colour, Cell* cell): Piece(colour, cell) {}

char Queen::getCharRep() const {
    return colour ? 'Q' : 'q';
}

vector<pair<int, int>> Queen::getCandidateTargets(const Board & board) const { return getLines(directions, board); }

const vector<pair<int, int>> Queen::directions = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};
