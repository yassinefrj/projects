#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../model/stratego.h"
#include "../utils/file_reader.h"
#include "../view/view.h"
namespace stratego {

class FileReader;
class Controller {

    stratego::Stratego& game;
    stratego::View& view;
public :

    /*!
     * \brief Controller Construct the controller for the game and the view
     * \param game the Stratego game
     * \param view the view of the Stratego game
     */
    Controller(stratego::Stratego& game ,  stratego::View& view);

    /*!
     * \brief getGame get a reference of the Stratego game
     * \return a reference of the stratego game
     */
    Stratego& getGame() const;

    /*!
     * \brief startFileGame start the game with the mode "Files Reading"
     * \param choice the difficulty
     * \param blue the path of the blue file
     * \param red the path of the red file
     */
    void startFileGame(int choice , std::string blue , std::string red);

    /*!
     * \brief startInteractiveGame start the game with the mode "Interactive Placement"
     * \param choice the difficulty
     */
    void startInteractiveGame(int choice);

    /*!
     * \brief clickSquare when a click is done in the game, the controller take care of it
     * \param pos the position of click
     */
    void clickSquare(const Position& pos);

};


}
#endif // CONTROLLER_H
