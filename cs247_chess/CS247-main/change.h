#ifndef INC_1225_CHANGE_H
#define INC_1225_CHANGE_H

#include <memory>
#include <utility>

class Board;

class Piece;

class Change {
    virtual void applyChange(Board &) = 0;
    virtual void removeChange(Board &) = 0;
protected:
    std::pair<int, int> start;
    std::pair<int, int> end;
    std::shared_ptr<Piece> piece;
public:
    Change(std::pair<int, int>, std::pair<int, int>,
           std::shared_ptr<Piece> piece = nullptr);
    void makeChange(Board &);
    void undoChange(Board &);
    std::pair<int, int> getStart();
    std::pair<int, int> getEnd();
    std::shared_ptr<Piece> getPiece();
    virtual ~Change();
};

class Shift : public Change {
    void applyChange(Board &) override;
    void removeChange(Board &) override;
public:
    Shift(std::pair<int, int>, std::pair<int, int>);
};

class AddPiece : public Change {
    void applyChange(Board &) override;
    void removeChange(Board &) override;
public:
    AddPiece(std::shared_ptr<Piece>, std::pair<int, int>);
};

class RemovePiece : public Change {
    void applyChange(Board &) override;
    void removeChange(Board &) override;
public:
    RemovePiece(std::pair<int, int>);
};

#endif //INC_1225_CHANGE_H
