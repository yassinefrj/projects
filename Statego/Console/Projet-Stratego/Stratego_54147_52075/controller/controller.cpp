#include "controller.h"

namespace stratego {
Controller::Controller(Stratego& game,View& view):
    game_{game}, view_{view} {
}

void Controller::start() {
    game_.registerObserver(&view_);

    do{

        switch (game_.getState()) {
        case State::NOT_STARTED:
            askConfigurationBoard();
            break;
        case State::INTERACTIVE_PLACEMENT:
            break;
        case State::IN_GAME_BEGINNER:
            selectPiece();
            break;
        case State::IN_GAME_NORMAL:
            selectPiece();
            break;
        case State::PIECE_NOT_SELECTED:
            selectPiece();
            break;
        case State::PIECE_SELECTED:
            movePiece();
            break;
        case State::TURN_PLAYED:
            selectPiece();
            break;
        case State::GAME_OVER:
            break;
        }

    }while(!game_.isFinish());
}

void Controller::selectPiece(){
    view_.askSelectSquare();
    game_.selectPiece(askPosition());
    if(game_.getState() ==  State::PIECE_SELECTED){
        askDeselectSquare();
    }
}

void Controller::movePiece(){
    view_.askMovement();
    game_.movePiece(askPosition());

}

void Controller::askDeselectSquare(){
    char answer;
    do{
        try{
            view_.askDeselectSquare();
            answer = nvs::lineFromKbd<char>();
            if(answer == 'Y' || answer =='y'){
                view_.askSelectSquare();
                game_.selectPiece(askPosition());
            }
        }catch(const std::exception & e){
            view_.displayError();
        }
    }while(answer != 'N' && answer != 'n');
}

Position Controller::askPosition(){
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

    switch(y){
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

    return Position(x,y);
}

Difficulty Controller::askDifficulty(){

    char answer;
    do
    {
        try
        {
            view_.askGameModChoice();
            answer = nvs::lineFromKbd<char>();
        }
        catch (const std::exception & e)
        {
            view_.displayError();
        }
    }
    while (answer != 'A' && answer != 'a' && answer != 'N' && answer != 'n' );



    if(answer == 'A' || answer == 'a'){
        return Difficulty::BEGINNER;
    }else {
        return Difficulty::NORMAL;
    }

}

void Controller::askConfigurationBoard(){
    FileReader fileRead {};
    view_.displayWelcome();

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
    while (answer != 'F' && answer != 'f' && answer != 'I' && answer != 'i' );

    if(answer == 'F' || answer == 'f'){
        fileRead.readFilePiece(game_);
        Difficulty  d = askDifficulty();
        game_.startStratego(d);
    }else if(answer == 'I' || answer=='i') {
        interactivePlacement();
    }
}

Position Controller::askPositionWithLimit(int rowMin, int rowMax){
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

            if(x >= rowMin || x <= rowMax)
                view_.showErrorPlacement(this->game_.getCurrentPlayerColor());
        }
        catch (const std::exception & e)
        {
            view_.displayError();
        }
    }
    while (x < rowMin || x > rowMax || y < 'A' || y > 'J');

    switch(y){
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

    return Position(x,y);
}

void Controller::interactivePlacement(){
    game_.interactivePlacement();
    view_.interactivePlacement();

    int fixedBluePiece = 0;
    int fixedRedPiece = 0;

    const int minRowBlue = 0;
    const int maxRowBlue = 3;

    const int minRowRed = 6;
    const int maxRowRed = 9;
    do{
        Position selectedPos;
        do{
            view_.askPlacementPosition(this->game_.getInteractiveRed().at(fixedRedPiece),Color::RED);
            selectedPos = askPositionWithLimit(minRowRed,maxRowRed);
        }while(!game_.getBoard().isFreeSquare(selectedPos));
        std::cout << "Ajout de pion" << std::endl;
        std::cout << this->game_.getInteractiveRed().at(fixedRedPiece) << std::endl;
        game_.addPiece(selectedPos,this->game_.getInteractiveRed().at(fixedRedPiece));
        fixedRedPiece++;
        game_.nextPlayerPlacement();

        do{
            view_.askPlacementPosition(this->game_.getInteractiveBlue().at(fixedBluePiece),Color::BLUE);
            selectedPos = askPositionWithLimit(minRowBlue,maxRowBlue);
        }while(!game_.getBoard().isFreeSquare(selectedPos));
        std::cout << "Ajout de pion " << std::endl;
        std::cout << this->game_.getInteractiveBlue().at(fixedBluePiece) << std::endl;
        game_.addPiece(selectedPos,this->game_.getInteractiveBlue().at(fixedBluePiece));
        fixedBluePiece++;
        game_.nextPlayerPlacement();

    }while(!game_.isFull());
    Difficulty  d = askDifficulty();
    game_.startStratego(d);

}


}
