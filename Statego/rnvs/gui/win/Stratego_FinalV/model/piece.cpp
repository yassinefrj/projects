#include "piece.h"

namespace stratego {

Piece::Piece(int level, Color color) :
    color_{color},level_{level},nbStepMax_{-1}{

    if(level< 0 || level > 11){
        throw std::invalid_argument("The level is not correct ! ");
    }

}

Piece::Piece(int level, Color color, int nbStepMax) :
    color_{color},level_{level},nbStepMax_{nbStepMax}{

    if(level< 0 || level > 11){
        throw std::invalid_argument("The level is not correct ! ");
    }else if(nbStepMax != 0 && nbStepMax != 1){
        throw std::invalid_argument("The number of step of"
                                    "a piece must be 0 or 1  ! ");
    }
}

int Piece::getLevel() const{
    return this->level_;
}

Color Piece::getColor() const{
    return this->color_;
}


int Piece::getStep() const{
    return this->nbStepMax_;

}

bool Piece::isVisible() const{
    return isVisible_;
}

void Piece::setVisible(bool isVisible){
    this->isVisible_ = isVisible;
}

bool Piece::isSameLevel(const Piece& piece){
    return piece.getLevel() == this->getLevel();
}

bool Piece::isStronger(const Piece& piece){
    return this->level_ > piece.getLevel() ;
}

std::ostream& operator<<(std::ostream& os, const Piece& p){
    std::string s ;

    switch(p.getLevel()){
    case 11 :
        s = "B";
        break;
    case 0 :
        s = "D";
        break;
    default:
        s =std::to_string(p.getLevel());
    }

    os << "   "<<s ;

    return os;
}


}
