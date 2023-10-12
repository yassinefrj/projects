#include "controller.h"

#include "model/stratego.h"     // rnvs : ajout
#include "view/view.h"          // rnvs : ajout
#include <iostream>             // rnvs : ajout
#include "utils/keyboard.hpp"   // rnvs : ajout
#include "utils/file_reader.h"  // rnvs : ajout

namespace stratego
{
Controller::Controller(Stratego & game, View & view):
    game_{game}, view_{view}
{
}


//le contoller gère les interaction user : add private methods.
void Controller::start()
{
    game_.registerObserver(&view_);

    do
    {

        switch (game_.getState())
        {
            case State::NOT_STARTED: // configuration
                std::cout << "NOT STARTED " << std::endl;
                askConfigurationBoard();
                break;
            case State::IN_GAME_BEGINNER:
                std::cout << "INGAME BEGINNER" << std::endl;
                selectPiece();
                break;
            case State::IN_GAME_NORMAL:
                std::cout << "INGAME  NORMAL" << std::endl;
                selectPiece();
                break;
            case State::PIECE_NOT_SELECTED:
                std::cout << "NOT Selected " << std::endl;
                selectPiece();
                break;
            case State::PIECE_SELECTED:
                std::cout << "SELECTED " << std::endl;
                movePiece();
                break;
            case State::TURN_PLAYED:
                std::cout << "turn played " << std::endl;
                selectPiece();
                break;
            case State::GAME_OVER:
                std::cout << "game over " << std::endl;
                break;
        }

    }
    while (!game_.isFinish());
}

void Controller::selectPiece()
{
    view_.askSelectSquare();
    game_.selectPiece(askPosition());
    if (game_.getState() ==  State::PIECE_SELECTED)
    {
        askDeselectSquare();
    }
}

void Controller::movePiece()
{
    view_.askMovement();
    game_.movePiece(askPosition());

}

void Controller::askDeselectSquare()
{
    char answer;
    do
    {
        try
        {
            view_.askDeselectSquare();
            answer = nvs::lineFromKbd<char>();
            if (answer == 'Y' || answer == 'y')
            {
                view_.askSelectSquare();
                game_.selectPiece(askPosition());
            }
        }
        catch (const std::exception & e)
        {
            view_.displayError();
        }
    }
    while (answer != 'N' && answer != 'n');
}

Position Controller::askPosition()
{
    int   x { -1 };
    char y { -1 };
    do
    {
        try
        {
            view_.askRow();
            x = nvs::lineFromKbd<int>();

            view_.askColumn();
            y = nvs::lineFromKbd<char>();
        }
        catch (const std::exception & e)
        {
            view_.displayError();
        }
    }
    while (x < 0 || x > 10 || y < 'A' || y > 'J');

    switch (y)
    {
        case 'A':
            y = 0;
            break;
        case 'B':
            y = 1;
            break;
        case 'C':
            y = 2;
            break;
        case 'D':
            y = 3;
            break;
        case 'E':
            y = 4;
            break;
        case 'F':
            y = 5;
            break;
        case 'G':
            y = 6;
            break;
        case 'H':
            y = 7;
            break;
        case 'I':
            y = 8;
            break;
        case 'J':
            y = 9;
            break;
    }

    return Position(x, y);
}

Difficulty Controller::askDifficulty()
{

    char answer;
    do
    {
        try
        {
            view_.askModChoice();
            answer = nvs::lineFromKbd<char>();
        }
        catch (const std::exception & e)
        {
            view_.displayError();
        }
    }
    while (answer != 'A' && answer != 'a' && answer != 'N' &&
            answer != 'n' );



    if (answer == 'A' || answer == 'a')
    {
        return Difficulty::BEGINNER;
    }
    else
    {
        return Difficulty::NORMAL;
    }



}

void Controller::askConfigurationBoard()
{
    FileReader fileRead {};
    view_.displayWelcome();
    Difficulty  d = askDifficulty();

    char answer;
    do
    {
        try
        {
            view_.askPlacementPieces();
            answer = nvs::lineFromKbd<char>();
        }
        catch (const std::exception & e)
        {
            view_.displayError();
        }
    }
    while (answer != 'F' && answer != 'f' && answer != 'I' &&
            answer != 'i' );

    if (answer == 'F' || answer == 'f')
    {
        fileRead.readFilePiece(game_);
        game_.startStratego(d);
    }
    else
    {
        interactivePlacement();
    }


}

void Controller::interactivePlacement()
{
    view_.interactivePlacement();
    game_.interactivePlacement();

}


}
