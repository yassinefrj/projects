#include "square.h"

namespace stratego {

Square::Square(Square_type typeCase,
               std::optional<Piece> piece)
    : typeCase_{typeCase},piece_{piece}
{}

bool Square::isLand() const{
    return this->typeCase_==Square_type::EARTH;
}

bool Square::isFree() const{
    return this->piece_ == std::nullopt;
}

std::optional <Piece>& Square::getPiece() {
    return this->piece_;
}

void Square::setPiece(std::optional<Piece> piece){
    this->piece_ = piece;
}


void Square::setSquareType(Square_type type){
    this->typeCase_ = type;
}

bool Square::isSameColor(Color& color){
    if(this->piece_ != std::nullopt){
        return this->piece_.value().getColor() == color;
    }
    return false;
}

void Square::removePiece(){
    this->piece_ = std::nullopt;
}

std::ostream& operator<<(std::ostream& os, const Square& sq){
    return os << (sq.Square::isLand() ? "|___|" : "| W |" ) ;
}

}
