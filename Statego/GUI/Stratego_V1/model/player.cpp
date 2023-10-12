#include "player.h"

namespace stratego {

Player::Player(Color color) :
    color_{color}{}

Color Player::getColor() const{
    return this->color_;
}

void Player::setColor(Color color){
    this->color_ = color;
}

std::ostream & operator<<(std::ostream & out, const Player & pl){
    switch (pl.getColor()) {
    case Color::BLUE:
        out << "Joueur BLEU";
        break;
    case Color::RED:
        out << "Joueur ROUGE";
        break;
    }
    return out;
}

}
