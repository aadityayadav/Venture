//
// Created by work on 2022-07-25.
//

#include "move.h"
#include "change.h"
#include "board.h"

#include <vector>
#include <memory>
#include <utility>

using namespace std;

Move::Move(bool colour, vector<shared_ptr<Change>> changes, pair<int, int> start, pair<int, int> end): colour{colour}, start{start}, end{end}, changes{changes} {}

void Move::makeMove(Board & board) {
    for (auto& change: changes) {
        change->makeChange(board);
    }
}

void Move::undoMove(Board & board) {
    for (int i = static_cast<int>(changes.size()) - 1; i >= 0; --i) {
        changes.at(i)->undoChange(board);
    }
}

pair<int, int> Move::getStart() const { return start; }

pair<int, int> Move::getEnd() const { return end; }

PromotionMove::PromotionMove(bool colour, std::pair<int, int> start, std::pair<int, int> end, char piece):
    Move{
        colour,
        {
            make_shared<RemovePiece>(start),
            make_shared<AddPiece>(Board::getPiece(piece), end)
        },
        start,
        end
    }
{}

RegularMove::RegularMove(bool colour, std::pair<int, int> start, std::pair<int, int> end):
    Move{
        colour,
        {
            make_shared<Shift>(start, end)
        },
        start,
        end
    }
{}

// TODO: CastleMove Constructor

CaptureMove::CaptureMove(bool colour, std::pair<int, int> start, std::pair<int, int> end):
    Move {
        colour,
        {
            make_shared<RemovePiece>(end),
            make_shared<Shift>(start, end)
        },
        start,
        end
    }
{}
