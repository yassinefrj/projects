#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model/stratego.h"
#include "utils/file_reader.h"
#include "view/view.h"
namespace stratego {

class FileReader;
class Controller {

    stratego::Stratego& game;
     stratego::View& view;
public :

    Controller(stratego::Stratego& game ,  stratego::View& view);
    Stratego getGame() const;

    void startGame(int choice , std::string blue , std::string red);

    void clickSquare(const Position& pos);
};


}
#endif // CONTROLLER_H
