//
// Created by work on 2022-07-25.
//

#include "board.h"
#include "cell.h"
#include "piece.h"
#include "move.h"

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

int Board::width = 8;

int Board::height = 8;

void Board::initializeGrid() {
    for (int i = 0; i < height; i++) {
        vector<Cell> row;
        for (int j = 0; j < width; j++) {
            row.push_back(make_pair(j, i));
        }
        grid.push_back(row);
    }

    for (int i = 0; i < width; i++) {
        char col = 'a' + i;
        addPiece('P', {col, '2'});
        addPiece('p', {col, '7'});
    }

    addPiece('R', "a1");
    addPiece('R', "h1");
    addPiece('r', "a8");
    addPiece('r', "h8");

    addPiece('N', "b1");
    addPiece('N', "g1");
    addPiece('n', "b8");
    addPiece('n', "g8");

    addPiece('B', "c1");
    addPiece('B', "f1");
    addPiece('b', "c8");
    addPiece('b', "f8");

    addPiece('Q', "d1");
    addPiece('q', "d8");

    addPiece('K', "e1");
    addPiece('k', "e8");
}

void Board::clearGrid() {
    for (vector<Cell> &row: grid) {
        for (Cell &c: row) {
            c.clear();
        }
    }
}

shared_ptr<Piece> Board::pieceAt(pair<int, int> coords) {
    return grid.at(coords.second).at(coords.first).piece;
}

void Board::plusPiece(shared_ptr<Piece> piece, pair<int, int> coords) {
    grid.at(coords.second).at(coords.first).addPiece(piece);
}

shared_ptr<Piece> Board::minusPiece(std::pair<int, int> coords) {
    return grid.at(coords.second).at(coords.first).clear();
}

void Board::addPiece(char c, string letters) {
    plusPiece(getPiece(c), getXY(letters));
}

void Board::removePiece(string letters) {
    minusPiece(getXY(letters));
}

vector<shared_ptr<Piece>> Board::getPieces(char lower, bool colour) const {
    vector<shared_ptr<Piece>> pieces;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid.at(i).size(); ++j) {
            if (!isFree({j, i}) && colourAt({j, i}) == colour) {
                Cell cell = grid.at(i).at(j);
                char c = cell.getChar();
                if (c == lower || c == toupper(lower))  pieces.push_back(cell.piece);
            }
        }
    }
    return pieces;
}

vector<shared_ptr<Piece>> Board::getPieces(char lower) const {
    vector<shared_ptr<Piece>> pieces = getPieces(lower, false);
    vector<shared_ptr<Piece>> otherPieces = getPieces(lower, true);
    pieces.reserve(pieces.size() + otherPieces.size());
    pieces.insert(pieces.end(), otherPieces.begin(), otherPieces.end());
    return pieces;
}

vector<shared_ptr<Piece>> Board::getPieces(bool colour) const {
    vector<char> pieceTypes = {'k', 'q', 'p', 'r', 'b', 'n'};
    vector<shared_ptr<Piece>> pieces;

    for (auto pieceType: pieceTypes) {
        vector<shared_ptr<Piece>> otherPieces = getPieces(pieceType, colour);
        pieces.reserve(pieces.size() + otherPieces.size());
        pieces.insert(pieces.end(), otherPieces.begin(), otherPieces.end());
    }
    return pieces;
}

vector<shared_ptr<Piece>> Board::getPieces() const {
    vector<char> pieceTypes = {'k', 'q', 'p', 'r', 'b', 'n'};
    vector<shared_ptr<Piece>> pieces;

    for (auto pieceType: pieceTypes) {
        vector<shared_ptr<Piece>> otherPieces = getPieces(pieceType);
        pieces.reserve(pieces.size() + otherPieces.size());
        pieces.insert(pieces.end(), otherPieces.begin(), otherPieces.end());
    }
    return pieces;
}

bool Board::validateKings() const {
    vector<shared_ptr<Piece>> kings = getPieces('k');
    if (kings.size() != 2) return false;
    return kings.at(0)->getColour() != kings.at(1)->getColour();
}

bool Board::validatePawns() const {
    vector<shared_ptr<Piece>> pawns = getPieces('p');
    for (auto& pawn: pawns) {
        int row = pawn->getCoords().second;
        if (row == 0 || row == 7) return false;
    }
    return true;
}

Board::Board(): player{true} {
    initializeGrid();
}

void Board::setup() {
    clearGrid();

    string cmd, letters, colour;
    char c;

    while (cin >> cmd) {
        if (cmd == "+") {
            cin >> c >> letters;
            try {
                addPiece(c, letters);
            } catch (...) {
                cout << "An error occurred while attempting to place the piece!" << endl;
            }
        } else if (cmd == "-") {
            cin >> letters;
            try {
                removePiece(letters);
            } catch (...) {
                cout << "An error occurred while trying to remove a piece!" << endl;
            }
        } else if (cmd == "=") {
            cin >> colour;
            if (colour == "white") {
                player = true;
            } else if (colour == "black") {
                player = false;
            } else {
                cout << "An unknown colour was selected to go first!" << endl;
            }
        } else if (cmd == "done") {
            if (!validateKings()) {
                cout << "The board must contain exactly one king for each colour!" << endl;
            } else if (checkedPlayer().first) {
                cout << "The initial board cannot have a player in check!" << endl;
            } else if (!validatePawns()) {
                cout << "The initial board cannot have pawns on the first or last row!" << endl;
            } else {
                break;
            }
        }
    }
}

void Board::printBoard() const {
    for (auto r: grid) {
        for (auto c: r) {
            cout << c.getChar();
        }
        cout << endl;
    }
}

vector<shared_ptr<Move>> Board::getValidMoves(bool colour) {
    vector<shared_ptr<Move>> validMoves;
    for (auto& piece: getPieces(colour)) {
        for (auto& move: piece->getPossibleMoves(*this)) {
            move->makeMove(*this);
            pair<bool, bool> check = checkedPlayer();
            if (!check.first || check.second != colour) {
                validMoves.push_back(move);
            }
            move->undoMove(*this);
        }
    }
    return validMoves;
}

pair<bool, bool> Board::checkedPlayer() const {
    vector<shared_ptr<Piece>> kings = getPieces('k');
    for (auto& piece: getPieces()) {
        for (auto& target: piece->getPossibleTargets(*this)) {
            for (auto& k: kings) {
                if (k->getCoords() == target) return {true, k->getColour()};
            }
        }
    }
    return {false, false};
}

bool Board::getPlayer() const { return player; }

bool Board::colourAt(pair<int, int> coords) const {
    if (!isFree(coords)) {
        return grid.at(coords.second).at(coords.first).piece->getColour();
    }
    throw 0;
}

bool Board::isFree(pair<int, int> coords) const {
    return !grid.at(coords.second).at(coords.first).hasPiece();
}

pair<int, int> Board::getXY(string letters) {
    if (letters.length() != 2) throw 0;
    if (letters[0] < 97 || letters[0] > 122) throw 0;
    if (letters[1] < 48 || letters[1] > 57) throw 0;
    int x = letters[0] - 97;
    int y = height - (letters[1] - 48);
    if (!inBounds({x, y})) throw 0;
    return make_pair(x, y);
}

string Board::getLetters(pair<int, int> coords) {
    char xChar = coords.first + 97;
    char yChar = height - coords.second + 48;

    string output;
    output.push_back(xChar);
    output.push_back(yChar);

    return output;
}

bool Board::inBounds(pair<int, int> coords) {
    return coords.first >= 0 && coords.second >= 0 && coords.first < width && coords.second < height;
}

shared_ptr<Piece> Board::getPiece(char c) {
    bool colour = c < 90;
    c = tolower(c);

    switch(c) {
        case 'k':
            return make_shared<King>(colour);
        case 'q':
            return make_shared<Queen>(colour);
        case 'b':
            return make_shared<Bishop>(colour);
        case 'r':
            return make_shared<Rook>(colour);
        case 'n':
            return make_shared<Knight>(colour);
        case 'p':
            return make_shared<Pawn>(colour);
        default:
            throw 0;
    }
}
