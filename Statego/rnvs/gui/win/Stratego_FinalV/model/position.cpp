#include "position.h"

namespace stratego {

Position::Position(int x, int y) :
    x_ { x }, y_ { y }
{ }

int Position::x() const{
    return x_;
}

int Position::y() const{
    return y_;
}

void Position::x(int x){
    x_ = x;
}

void Position::y(int y){
    y_ = y;
}

bool Position::operator==(const Position & pos){
    return pos.x() == this->x_ && pos.y() == this->y_;
}

}
