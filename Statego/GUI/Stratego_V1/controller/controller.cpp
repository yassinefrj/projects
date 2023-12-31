#include "controller.h"
#include <QDebug>


namespace stratego{



Controller::Controller(Stratego &game, View &view) : game{game}, view{view}{
    this->view.setCtrl(this);
}

Stratego Controller::getGame() const{
    return this->game;
}




void Controller::startGame(int choice, std::string blue, std::string red){
    game.registerObserver(&view);
    FileReader fileRead {};
    fileRead.readFilePiece(game,blue,red);
    stratego::Difficulty d = stratego::Difficulty::BEGINNER;

    if(choice ==0){
        d = stratego::Difficulty::BEGINNER;
    }else{
        d = stratego::Difficulty::NORMAL;
    }
    game.startStratego(d);
}

void Controller::clickSquare(const Position &pos){
    switch (this->game.getState()) {
    case State::NOT_STARTED:
        break;
    case State::INTERACTIVE_PLACEMENT:
        break;
    case State::IN_GAME_NORMAL:
        this->game.selectPiece(pos);
        break;
    case State::IN_GAME_BEGINNER:
         this->game.selectPiece(pos);
        break;
    case State::PIECE_NOT_SELECTED:
        this->game.selectPiece(pos);
        break;
    case State::PIECE_SELECTED:
        this->game.movePiece(pos);
        break;
    case State::TURN_PLAYED:
        this->game.nextPlayerPlacement();
        this->game.selectPiece(pos);
        this->game.isFinish();
        break;
    case State::GAME_OVER:
        break;
    }
}


}







