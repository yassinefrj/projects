#include "stratego.h"

namespace stratego {

Stratego::Stratego() : difficulty_{Difficulty::BEGINNER}
  ,state_{State::NOT_STARTED},currentPlayer_{0}{
    this->players_[0].setColor(Color::RED); // le Red est le premier joueur à jouer !
    this->players_[1].setColor(Color::BLUE);
    this->board_=Board();
    this->selected_ = Position(-1,-1);
}

void Stratego::startStratego(const Difficulty& difficulty){
    if(this->state_ != State::NOT_STARTED && this->state_ != State::INTERACTIVE_PLACEMENT
            &&this->state_ != State::GAME_OVER&&this->state_ != State::QUIT){
        throw std::invalid_argument("This game state is not expected ! ");
    }else{
        this->currentPlayer_ =0;
        switch (difficulty) {
        case Difficulty::BEGINNER:
            this->state_ = State::IN_GAME_BEGINNER;
            this->difficulty_ = Difficulty::BEGINNER;
            notifyObservers();
            break;
        case Difficulty::NORMAL:
            this->state_ = State::IN_GAME_NORMAL;
            this->difficulty_ = Difficulty::NORMAL;
            notifyObservers();
            break;
        }
    }
}

void Stratego::startInteractivPlacemement(const Difficulty& d){
    this->state_ = State::INTERACTIVE_PLACEMENT;
    this->difficulty_ = d;
}



bool Stratego::isSelectionExact(const Position& pos){
    Color currentPlayerColor = this->players_[currentPlayer_].getColor();
    if(board_.isInside(pos) &&
            board_.isLand(pos) &&
            !board_.isFreeSquare(pos)&&
            board_.isSameColor(pos,currentPlayerColor) &&
            board_.getPiece(pos)->getLevel() != 0 &&
            board_.getPiece(pos)->getLevel() != 11){
        this->selected_ = pos;
        return true;
    }else{
        this->selected_ = Position(-1,-1);
        this->state_ = State::PIECE_NOT_SELECTED;
        notifyObservers();
    }

    return false;

}

void Stratego::selectPiece(const Position& pos){
    if(isSelectionExact(pos)){
        this->state_ = State::PIECE_SELECTED;
        notifyObservers();
    }


}

void Stratego::addPiece(const Position& pos,Piece piece){
    this->board_.addPiece(pos,piece);
}

void Stratego::attack(const Position& pos){
    if(this->state_ != State::PIECE_SELECTED){
        throw std::invalid_argument("This game state is not expected ! ");
    }

    if((board_.getPiece(this->selected_)->getLevel()== 1
        && board_.getPiece(pos)->getLevel() ==10)
            ||(board_.getPiece(this->selected_)->getLevel() == 3
               && board_.getPiece(pos)->getLevel() ==11)){

        Piece dead = board_.getSquare(pos).getPiece().value();
        this->deadPieces_.push_back(dead);
        this->board_.removePiece(pos);
        this->board_.getPiece(this->selected_)->setVisible(true);

        movePieceNormal(pos);

    }else{

        if(board_.getPiece(selected_).value().isSameLevel(board_.getPiece(pos).value())){
            this->deadPieces_.push_back(board_.getPiece(selected_).value());
            this->deadPieces_.push_back(board_.getPiece(pos).value());
            this->board_.removePiece(pos);
            this->board_.removePiece(this->selected_);
            turnPlayed();

        }else if (board_.getPiece(selected_).value().isStronger(board_.getPiece(pos).value())){
            Piece dead = board_.getSquare(pos).getPiece().value();
            this->deadPieces_.push_back(dead);
            this->board_.removePiece(pos);
            this->board_.getPiece(this->selected_)->setVisible(true);
            if(board_.getPiece(selected_).value().getLevel() == 2) {
                movePieceScout(pos);
            }else{
                movePieceNormal(pos);
            }

        }else{
            Piece dead = board_.getSquare(this->selected_).getPiece().value();
            this->deadPieces_.push_back(dead);
            this->board_.removePiece(this->selected_);
            this->board_.getPiece(pos)->setVisible(true);
            turnPlayed();
        }
    }

}

void Stratego::movePieceNormal(const Position& pos){
    if(this->state_ != State::PIECE_SELECTED){
        throw std::invalid_argument("This game state is not expected ! ");
    }

    Position NORD = Position(this->selected_.x()-1,this->selected_.y());
    Position SUD = Position(this->selected_.x()+1,this->selected_.y());
    Position LEFT = Position(this->selected_.x(),this->selected_.y()-1);
    Position RIGHT = Position(this->selected_.x(),this->selected_.y()+1);


    if(squareInsideLand(pos)){
        if((NORD == pos ) ||
                (SUD == pos  ) ||
                (LEFT == pos)||
                (RIGHT == pos)){

            if(board_.getPiece(pos)->getColor() != players_[currentPlayer_].getColor() &&
                    board_.getPiece(pos) != std::nullopt){
                attack(pos);


            }else if (board_.getPiece(pos)->getColor() == players_[currentPlayer_].getColor() &&
                      board_.getPiece(pos) != std::nullopt){
                this->selected_ = Position(-1,-1);
                this->state_ = State::PIECE_NOT_SELECTED;
                notifyObservers();

            }else {

                Piece p = board_.getSquare(this->selected_).getPiece().value();
                this->board_.addPiece(pos,p);
                this->board_.removePiece(this->selected_);
                turnPlayed();
            }
        }else{
            this->selected_ = Position(-1,-1);
            this->state_ = State::PIECE_NOT_SELECTED;
            notifyObservers();
        }
    }else{
        state_ = State::PIECE_SELECTED;
        notifyObservers();
    }

}

void Stratego::movePieceScout(const Position& pos){
    if(this->state_ != State::PIECE_SELECTED){
        throw std::invalid_argument("This game state is not expected ! ");
    }

    int  top {0};
    int bottom {0};
    int left {0};
    int right{0};

    if(this->selected_.x() > pos.x() ){
        top = 1;
    }else if(this->selected_.x() < pos.x() ){
        bottom = 1;
    }else if (this->selected_.y() < pos.y() ){
        right = 1;
    }else if (this->selected_.y() > pos.y() ){
        left= 1;
    }

    Square squareStart;
    Position posStart = this->selected_;
    bool isFree{true};

    while(!(posStart == pos) ){
        posStart.x(posStart.x() + bottom);
        posStart.x(posStart.x() - top);
        posStart.y(posStart.y() - left);
        posStart.y(posStart.y() + right);
        squareStart = this->board_.getSquare(posStart);
        if(!squareStart.isLand() || !squareStart.isFree()){
            isFree = false;
            break;
        }
    }

    if(isFree){
        Piece p = board_.getSquare(this->selected_).getPiece().value();
        this->board_.addPiece(pos,p);
        this->board_.removePiece(this->selected_);
        turnPlayed();
    }else if(this->board_.getPiece(posStart)->getColor()
             !=board_.getPiece(selected_)->getColor()){
        if(!(posStart == pos) ){
            this->selected_ = Position(-1,-1);
            state_ = State::PIECE_NOT_SELECTED;
            notifyObservers();
        }else{
            attack(posStart);
        }
    }else{
        this->selected_ = Position(-1,-1);
        state_ = State::PIECE_NOT_SELECTED;
        notifyObservers();
    }

}

void Stratego::movePiece(const Position& pos){
    int pieceStep = this->board_.getPiece(this->selected_)->getStep();
    switch(pieceStep){
    case -1 :
        if(isMoveScoutExact(this->selected_,pos)){
            movePieceScout(pos);
        }else{
            this->selected_ = Position(-1,-1);
            this->state_ = State::PIECE_NOT_SELECTED;
            notifyObservers();
        }
        break;
    case 1 :
        movePieceNormal(pos);
        break;

    }

}

Position Stratego::getSelected()
{
    return this->selected_;
}

Board Stratego::getBoard() const{
    return this->board_;
}

State Stratego::getState() const{
    return this->state_;
}

bool Stratego::isFinish()  {
    for (int i{0}; i < static_cast<int>(deadPieces_.size()); i++) {
        if(deadPieces_.at(i).getLevel() == 0 &&
                deadPieces_.at(i).getColor() == Color::BLUE){
            this->currentPlayer_ = 1;
            state_ = State::GAME_OVER;
            clearBoard();
            notifyObservers();
            state_ = State::NOT_STARTED;
            deadPieces_.clear();
            return true;
        }else if ( deadPieces_.at(i).getLevel() == 0 &&
                   deadPieces_.at(i).getColor() == Color::RED){
            this->currentPlayer_ = 0;
            state_ = State::GAME_OVER;
            clearBoard();
            notifyObservers();
            state_ = State::NOT_STARTED;
            deadPieces_.clear();
            return true;
        }
    }

    int deadBlueMovable{0};
    int deadRedMovable{0};
    for (int i{0}; i < static_cast<int>(deadPieces_.size()); i++) {
        if(deadPieces_.at(i).getLevel() != 0 &&
                deadPieces_.at(i).getLevel() != 11){
            if(deadPieces_.at(i).getColor() == Color::BLUE){
                deadBlueMovable++;
            }else{
                deadRedMovable++;
            }
        }
    }

    if(deadBlueMovable == 33 ){
        this->currentPlayer_ = 1;
        state_ = State::GAME_OVER;
        clearBoard();
        notifyObservers();
        state_ = State::NOT_STARTED;
        deadPieces_.clear();
        return true;
    }else if (deadRedMovable == 33){
        this->currentPlayer_ = 0;
        state_ = State::GAME_OVER;
        clearBoard();
        notifyObservers();
        state_ = State::NOT_STARTED;
        deadPieces_.clear();
        return true;
    }

    return false;
}

bool Stratego::isFullCorrectly() {
    int nbPieces = 0;
    for(int i{0} ; i < 10; i++){
        for(int j{0}; j < 10 ; j++){
            if(this->board_.getPiece(Position(i,j)) != std::nullopt){
                nbPieces++;
            }
        }
    }
    return nbPieces == 80;

}

Color Stratego::getCurrentPlayerColor() const{

    return this->players_[currentPlayer_].getColor();
}

Difficulty Stratego::getDifficulty() const{
    if(this->state_ == State::NOT_STARTED ){
        throw std::invalid_argument("This game state is not expected ! ");
    }
    return this->difficulty_;
}

void Stratego::turnPlayed(){
    if(state_ != State::PIECE_SELECTED){
        throw std::invalid_argument("This game state is not expected !  ");
    }else{
        this->state_ = State::TURN_PLAYED;
        switchPlayer();
        notifyObservers();
    }

}

void Stratego::interactivePlacement(){
    if(state_ != State::NOT_STARTED){
        throw std::invalid_argument("This game state is not expected ! ");
    }else{
        clearBoard();
        interactiveBlue.clear();
        interactiveRed.clear();
    }
    Color red = Color::RED;
    Color blue = Color::BLUE;

    interactiveBlue.push_back(Piece(1,blue,1));
    interactiveRed.push_back(Piece(1,red,1));
    interactiveBlue.push_back(Piece(10,blue,1));
    interactiveRed.push_back(Piece(10,red,1));
    interactiveBlue.push_back(Piece(9,blue,1));
    interactiveRed.push_back(Piece(9,red,1));
    interactiveBlue.push_back(Piece(0,blue,0));
    interactiveRed.push_back(Piece(0,red,0));

    for(int eclaireur{0}; eclaireur < 16; eclaireur++){
        if(eclaireur >= 8){
            interactiveBlue.push_back(Piece(2,blue));
        }else{
            interactiveRed.push_back(Piece(2,red));
        }
    }

    for(int demineur{0}; demineur < 10; demineur++){
        if(demineur >= 5){
            interactiveBlue.push_back(Piece(3,blue,1));
        }else{
            interactiveRed.push_back(Piece(3,red,1));
        }
    }

    for(int sergent{0}; sergent < 8; sergent++){
        if(sergent >= 4){
            interactiveBlue.push_back(Piece(4,blue,1));
        }else{
            interactiveRed.push_back(Piece(4,red,1));
        }
    }

    for(int lieutenant{0}; lieutenant < 8; lieutenant++){
        if(lieutenant >= 4){
            interactiveBlue.push_back(Piece(5,blue,1));
        }else{
            interactiveRed.push_back(Piece(5,red,1));
        }
    }

    for(int commandant{0}; commandant < 8; commandant++){
        if(commandant >= 4){
            interactiveBlue.push_back(Piece(6,blue,1));
        }else{
            interactiveRed.push_back(Piece(6,red,1));
        }
    }

    for(int major{0}; major < 6; major++){
        if(major >= 3){
            interactiveBlue.push_back(Piece(7,blue,1));
        }else{
            interactiveRed.push_back(Piece(7,red,1));
        }
    }

    for(int colonel{0}; colonel < 4; colonel++){
        if(colonel >= 2){
            interactiveBlue.push_back(Piece(8,blue,1));
        }else{
            interactiveRed.push_back(Piece(8,red,1));
        }
    }

    for(int bombe{0}; bombe < 12; bombe++){
        if(bombe >= 6){
            Piece p{11,blue,0};
            interactiveBlue.push_back(p);
        }else{
            interactiveRed.push_back(Piece(11,red,0));
        }
    }
    this->state_ = State::INTERACTIVE_PLACEMENT;
    notifyObservers();
}

std::vector<Piece> Stratego::getInteractiveBlue() const {
    return interactiveBlue;
}
std::vector<Piece> Stratego::getInteractiveRed() const {
    return interactiveRed;
}


bool Stratego::squareInsideLand(const Position& pos){
    return board_.isInside(pos) &&  board_.isLand(pos);
}

bool Stratego::isMoveScoutExact(const Position& start,const Position& end){
    return (start.x() > end.x() && start.y() == end.y())
            || (start.x() < end.x() && start.y() == end.y())
            || (start.y() < end.y() && start.x() == end.x())
            || (start.y() > end.y() && start.x() == end.x());

}

void Stratego::switchPlayer(){
    if(this->state_ != State::TURN_PLAYED
            && this->state_ != State::INTERACTIVE_PLACEMENT){
        throw std::invalid_argument("This game state is not expected ! ");
    }else{
        if(this->currentPlayer_ == 0){
            currentPlayer_ = 1;
        }else{
            currentPlayer_ = 0;
        }
    }
}


void Stratego::clearBoard(){
    for(int i{0};  i < 10; i++){
        for(int j{0}; j < 10; j++){
            this->board_.removePiece(Position(i,j));
        }
    }

}

bool Stratego::isFull() const{
    int nbPiece = 0;
    for(int i{0} ; i < 10; i++){
        for(int j{0}; j < 10 ; j++){
            if(this->board_.getSquare(Position(i,j)).getPiece() != std::nullopt){
                nbPiece++;
            }
        }
    }
    return nbPiece == 80;
}

void Stratego::nextPlayerPlacement(){
    if(this->state_ == State::INTERACTIVE_PLACEMENT){
        switchPlayer();
        notifyObservers();
    }
}

void Stratego::quitGame(){
    this->state_ = State::QUIT;
    this->clearBoard();
    this->selected_ = Position(-1,-1);
    deadPieces_.clear();
    this->
    notifyObservers();
    this->state_ = State::NOT_STARTED;
}

std::vector<Piece> &Stratego::getDeadPiece()
{
return this->deadPieces_;
}


}
