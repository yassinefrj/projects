#include "board.h"

#include "position.h"   // rnvs : include / déclaration anticipée

namespace stratego
{


Board::Board()
{
    this->board_[4][2].setSquareType(Square_type::WATER);
    this->board_[4][3].setSquareType(Square_type::WATER);
    this->board_[4][6].setSquareType(Square_type::WATER);
    this->board_[4][7].setSquareType(Square_type::WATER);
    this->board_[5][2].setSquareType(Square_type::WATER);
    this->board_[5][3].setSquareType(Square_type::WATER);
    this->board_[5][6].setSquareType(Square_type::WATER);
    this->board_[5][7].setSquareType(Square_type::WATER);
}

std::array<std::array<Square, 10>, 10> Board::getBoard() const
{
    return this->board_;
}

Square Board::getSquare(const Position & pos) const
{
    return board_[pos.x()][pos.y()];
}

bool Board::isInside(const Position & pos)
{
    return (pos.x() < 10 && pos.y() < 10
            && pos.x() >= 0
            && pos.y() >= 0);
}

bool Board::isSameColor(const Position & pos, Color color)
{
    return board_[pos.x()][pos.y()].isSameColor(color);
}

bool Board::isFreeSquare(const Position & pos)
{
    return board_[pos.x()][pos.y()].isFree();
}

void Board::addPiece(const Position & pos, Piece piece)
{
    board_[pos.x()][pos.y()].setPiece(piece);
}

void Board::removePiece(const Position & pos)
{
    board_[pos.x()][pos.y()].removePiece();
}

bool Board::isLand(const Position & pos)
{
    return board_[pos.x()][pos.y()].isLand();
}

std::optional<Piece> & Board::getPiece(const Position & pos)
{
    return board_[pos.x()][pos.y()].getPiece();
}
}

