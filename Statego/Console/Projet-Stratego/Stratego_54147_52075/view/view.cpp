#include "view.h"

namespace stratego {

View::View(Stratego& model) : model_{model}{}

void View::askPlacementPieces(){
    std::cout << "Comment voulez-vous placer vos pions ?"
                 " (Interactivement : I , Fichier configuration : F)\n"
                 "Entrez la lettre : " << std::endl;
}

void View::interactivePlacement(){
    std::cout << "Bienvenue dans le placement interactif :) " << std::endl;


}

void View::displayWelcome(){
    std::cout << "******Bienvenue dans le jeu Stratego ! ******* " << std::endl;
    std::cout << "------------------54147 / 52075-------------- " << std::endl;

}

void View::askMovement(){
    std::cout << "Dans quelle case voulez-vous placer le pion ? " << std::endl;
}

void View::askSelectSquare(){
    std::cout << "Entrez les valeurs de l'emplacement du pion  : " << std::endl;
}

void View::askRow(){

    std::cout << "Choisissez le numero de la ligne (0-9) :";

}

void View::askColumn(){
    std::cout << "Choisissez la lettre  (A-J) qui concorde "
                 "avec la colonne du plateau : ";

}

void View::displayError(){
    std::cout << "La valeur n'est pas la bonne , merci de "
                 "de mettre une valeur valide  !  : "  <<  std::endl;
}

void View::askDeselectSquare(){
    std::cout << "Souhaitez-vous un autre pion ? Y / N : ";
}

void View::askGameModChoice(){
    std::cout << "Quel mode de jeu choisissez-vous ? \n"
                 "(N-normal,A-amateur) : " << std::endl;

}

void View::askPlacementPosition(const std::string  & piece ,const Color color){
    std::cout << color << " : Ou souhaitez-vous placer le pion " << piece << " ?" << std::endl;
}

void View::askPlacementPosition(const Piece  & piece ,const Color color){
    std::cout << color << " : Ou souhaitez-vous placer le pion " << piece << " ?" << std::endl;
}


void View::showBoardBeginner(Color color){
    std::cout << "****************************************" << std::endl;
    std::cout << "Affichage du plateau de jeu pour le joueur : ";
    switch (color) {
    case Color::BLUE:
        std::cout << "Bleu ";
        break;
    case Color::RED:
        std::cout << "Rouge";
        break;
    }
    std::cout << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "    ";
    for (char cpt{65}; cpt < 75; cpt++)
        std::cout << cpt << "     ";
    for (int row {0} ; row < 10 ; row++ ) {
        std::cout<<std::endl;
        for(int column{0}; column < 10 ; column++){
            if(column == 0){
                std::cout << row << " ";
            }
            stratego::Position pos(row,column);

            if(model_.getBoard().getSquare(pos).getPiece() != std::nullopt &&
                    (model_.getBoard().getSquare(pos).getPiece()->getColor() == color ||
                     model_.getBoard().getSquare(pos).getPiece()->isVisible())){
                switch (model_.getBoard().getSquare(pos).getPiece()->getLevel()) {
                case 11:
                    std::cout<<"|_" << "B" << "_|"<<" ";
                    break;
                case 0 :
                    std::cout<<"|_" << "D" << "_|"<<" ";
                    break;
                case 10 :
                    std::cout<<"| " << "10" << "|"<<" ";
                    break;
                default:
                    std::cout<<"|_"<<model_.getBoard().getSquare(pos).getPiece()->getLevel()<< "_|"<<" ";
                    break;
                }
            }else if(model_.getBoard().getSquare(pos).getPiece() != std::nullopt &&
                     model_.getBoard().getSquare(pos).getPiece()->getColor() != color){
                std::cout << "|_?_| ";
            }else{
                std::cout<<model_.getBoard().getSquare(pos)<<" ";
            }
            if(column ==9){
                std::cout<<std::endl;

            }
        }
    }

}

void View::showBoardNormal(Color color){
    std::cout << "****************************************" << std::endl;
    std::cout << "Affichage du plateau de jeu pour le Joueur : ";
    switch (color) {
    case Color::BLUE:
        std::cout << "Bleu";
        break;
    case Color::RED:
        std::cout << "Rouge";
        break;
    }
    std::cout << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "    ";
    for (char cpt{65}; cpt < 75; cpt++)
        std::cout << cpt << "     ";
    for (int row {0} ; row < 10 ; row++ ) {
        std::cout<<std::endl;
        for(int column{0}; column < 10 ; column++){
            if(column == 0){
                std::cout << row << " ";
            }
            stratego::Position pos(row,column);

            if(model_.getBoard().getSquare(pos).getPiece() != std::nullopt &&
                    model_.getBoard().getSquare(pos).getPiece()->getColor() == color){
                switch (model_.getBoard().getSquare(pos).getPiece()->getLevel()) {
                case 11:
                    std::cout<<"|_" << "B" << "_|"<<" ";
                    break;
                case 0 :
                    std::cout<<"|_" << "D" << "_|"<<" ";
                    break;
                case 10 :
                    std::cout<<"| " << "10" << "|"<<" ";
                    break;
                default:
                    std::cout<<"|_"<<model_.getBoard().getSquare(pos).getPiece()->getLevel()<< "_|"<<" ";
                    break;
                }
            }else if(model_.getBoard().getSquare(pos).getPiece() != std::nullopt &&
                     model_.getBoard().getSquare(pos).getPiece()->getColor() != color){
                std::cout << "|_?_| ";
            }else{
                std::cout<<model_.getBoard().getSquare(pos)<<" ";
            }
            if(column ==9){
                std::cout<<std::endl;

            }
        }
    }

}

void View::showErrorSelection(){
    std::cout << "Merci de chosir une case vous appartenant et transposable" << std::endl;

}

void View::showErrorPlacement(Color color){
    std::cout << "Merci de chosir une case vous appartenant, vide et de type terre : " << std::endl;
    if(color == Color::RED){
        std::cout << "Entre la ligne 6 & 9 " << std::endl;
    }else{
        std::cout << "Entre la ligne 0 & 3" << std::endl;
    }

}

void View::displayTurnBoard(){
    std::cout << "Changement de joueur ...." << std::endl;
    if(model_.getDifficulty() == Difficulty::BEGINNER){
        this->showBoardBeginner(model_.getCurrentPlayerColor());
    }else{
        this->showBoardNormal(model_.getCurrentPlayerColor());
    }
}

void View::showWinner(){
    if(model_.getCurrentPlayerColor() == Color::RED){
        std::cout << "Bravo , le gagnant est : " << Color::BLUE << " "  << std::endl;
    }else{
        std::cout << "Bravo , le gagnant est : " << Color::RED << " "  << std::endl;

    }

}

void View::update(const nvs::Subject *subject){
    switch (model_.getState()) {
    case State::NOT_STARTED:
        this->displayWelcome();
        break;
    case State::INTERACTIVE_PLACEMENT:
        this->showBoardNormal(model_.getCurrentPlayerColor());
        break;
    case State::IN_GAME_NORMAL:
        this->showBoardNormal(model_.getCurrentPlayerColor());
        break;
    case State::IN_GAME_BEGINNER:
        this->showBoardBeginner(model_.getCurrentPlayerColor());
        break;
    case State::PIECE_NOT_SELECTED:
        this->showErrorSelection();
        break;
    case State::PIECE_SELECTED:
        this->askMovement();
        break;
    case State::TURN_PLAYED:
        this->displayTurnBoard();
        break;
    case State::GAME_OVER:
        this->showWinner();
        break;
    }

}

}
