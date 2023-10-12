#include "view.h"

#include <iostream>     // rnvs : ajout
#include "model/color.h"    // rnvs : ajout
#include "model/player.h"   // rnvs : ajout pour View::askPlacementPosition(std::string piece, Color color)
#include "model/position.h" // rnvs : ajout
#include "model/stratego.h" // rnvs : ajout

namespace stratego
{

View::View(Stratego & model) : model_{model} {}

void View::askPlacementPieces()
{
    std::cout <<
              "Comment voulez-vous placer vos pions ? (Interactivement : I , "
              "Fichier configuration : F) Entrez la lettre : ";
}

void View::interactivePlacement()
{
    std::cout << "Bienvenue dans le placement interactif :) " <<
              std::endl;
    std::cout << "Le plateau de jeu  Bleu : " << std::endl;
    showBoardNormal(Color::BLUE);
    std::cout << "Le plateau de jeu  Rouge : " << std::endl;
    showBoardNormal(Color::RED);


}

void View::displayWelcome()
{
    std::cout << "Bienvenue dans le jeu Stratego ! " << std::endl;
    std::cout << "           54147 / 52075 " << std::endl;

}

void View::askMovement()
{
    std::cout << "Dans quelle case voulez-vous placer le pion ? " <<
              std::endl;
}

void View::askSelectSquare()
{
    std::cout << "Entrez les valeurs de l'emplacement du pion  : " <<
              std::endl;
}

void View::askRow()
{

    std::cout << "Choisissez le numéro de la ligne (1-10) :";

}

void View::askColumn()
{
    std::cout <<
              "Choisissez la lettre  (A-J) qui concorde avec la colonne du plateau : ";

}

void View::displayError()
{
    std::cout << "La valeur n'est pas la bonne , merci de "
              "de mettre une valeur valide  !  : "  <<  std::endl;
}

void View::askDeselectSquare()
{
    std::cout << "Souhaitez-vous un autre pion ? O / N : ";
}

void View::askModChoice()
{
    std::cout <<
              "Quel mode de jeu choisissez-vous : (N-normal,A-amateur) : " <<
              std::endl;

}

void View::askPlacementPosition(std::string piece, Color color)
{
    std::cout << color << " : Ou souhaitez-vous placer le pion " << piece
              << " ?" << std::endl;
    // rnvs : il n'y a pas d'operator<<(std::ostream &, const Color &)
    // rnvs : ici, c'est std::ostream & operator<<(std::ostream & out, const Player & pl);
    //        qui est invoqué à travers Player(Color color = Color::RED);

}

void View::showBoardBeginner(Color color)
{
    std::cout << "****************************************" << std::endl;
    std::cout << "Affichage du plateau de jeu pour le joueur : ";
    switch (color)
    {
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
    for (int row {0} ; row < 10 ; row++ )
    {
        std::cout << std::endl;
        for (int column{0}; column < 10 ; column++)
        {
            if (column == 0)
            {
                std::cout << row << " ";
            }
            stratego::Position pos(row, column);

            if (model_.getBoard().getSquare(pos).getPiece() != std::nullopt &&
                    (model_.getBoard().getSquare(pos).getPiece()->getColor() == color ||
                     model_.getBoard().getSquare(pos).getPiece()->isVisible()))
            {
                switch (model_.getBoard().getSquare(pos).getPiece()->getLevel())
                {
                    case 11:
                        std::cout << "|_" << "B" << "_|" << " ";
                        break;
                    case 0 :
                        std::cout << "|_" << "D" << "_|" << " ";
                        break;
                    case 10 :
                        std::cout << "| " << "10" << "|" << " ";
                        break;
                    default:
                        std::cout << "|_" << model_.getBoard().getSquare(
                                      pos).getPiece()->getLevel() << "_|" << " ";
                        break;
                }
            }
            else if (model_.getBoard().getSquare(pos).getPiece() != std::nullopt
                     &&
                     model_.getBoard().getSquare(pos).getPiece()->getColor() != color)
            {
                std::cout << "|_?_| ";
            }
            else
            {
                std::cout << model_.getBoard().getSquare(pos) << " ";
            }
            if (column == 9)
            {
                std::cout << std::endl;

            }
        }
    }

}

void View::showBoardNormal(Color color)
{
    // Gerer la gestion pour cacher le joueur OU modifier getBoard()
    std::cout << "****************************************" << std::endl;
    std::cout << "Affichage du plateau de jeu pour le Joueur : ";
    switch (color)
    {
        case Color::BLUE:
            std::cout << "BLUE";
            break;
        case Color::RED:
            std::cout << "RED";
            break;
    }
    std::cout << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "    ";
    for (char cpt{65}; cpt < 75; cpt++)
        std::cout << cpt << "     ";
    for (int row {0} ; row < 10 ; row++ )
    {
        std::cout << std::endl;
        for (int column{0}; column < 10 ; column++)
        {
            if (column == 0)
            {
                std::cout << row << " ";
            }
            stratego::Position pos(row, column);

            if (model_.getBoard().getSquare(pos).getPiece() != std::nullopt &&
                    model_.getBoard().getSquare(pos).getPiece()->getColor() == color)
            {
                switch (model_.getBoard().getSquare(pos).getPiece()->getLevel())
                {
                    case 11:
                        std::cout << "|_" << "B" << "_|" << " ";
                        break;
                    case 0 :
                        std::cout << "|_" << "D" << "_|" << " ";
                        break;
                    case 10 :
                        std::cout << "| " << "10" << "|" << " ";
                        break;
                    default:
                        std::cout << "|_" << model_.getBoard().getSquare(
                                      pos).getPiece()->getLevel() << "_|" << " ";
                        break;
                }
            }
            else if (model_.getBoard().getSquare(pos).getPiece() != std::nullopt
                     &&
                     model_.getBoard().getSquare(pos).getPiece()->getColor() != color)
            {
                std::cout << "|_?_| ";
            }
            else
            {
                std::cout << model_.getBoard().getSquare(pos) << " ";
            }
            if (column == 9)
            {
                std::cout << std::endl;

            }
        }
    }

}

void View::update(const nvs::Subject * subject)
{
    switch (model_.getState())
    {
        case State::NOT_STARTED:
            this->displayWelcome();
            break;
        case State::IN_GAME_NORMAL:
            this->showBoardNormal(model_.getCurrentPlayerColor());
            break;
        case State::IN_GAME_BEGINNER:
            this->showBoardBeginner(model_.getCurrentPlayerColor());
            break;
        case State::PIECE_NOT_SELECTED:
            std::cout <<
                      "Merci de chosir une case vous appartenant et transposable" <<
                      std::endl;
            break;
        case State::PIECE_SELECTED:
            std::cout << "Merci de faire un mouvement permit " << std::endl;
            break;
        case State::TURN_PLAYED:
            std::cout << "Changement de joueur ...." << std::endl;
            if (model_.getDifficulty() == Difficulty::BEGINNER)
            {
                this->showBoardBeginner(model_.getCurrentPlayerColor());
            }
            else
            {
                this->showBoardNormal(model_.getCurrentPlayerColor());
            }
            break;
        case State::GAME_OVER:
            std::cout << "Bravo , le gagnant est : " <<
                      model_.getCurrentPlayerColor() << " "  << std::endl;
            break;
    }

}

}
