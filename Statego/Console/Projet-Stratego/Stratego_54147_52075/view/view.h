#ifndef VIEW_H
#define VIEW_H

#include "utils/observer.h"
#include "model/stratego.h"

namespace stratego {

class Subject;

class View : public nvs::Observer {

private :
    stratego::Stratego& model_ ;

public:

    /*!
     * @brief Constructor of view.
     * @param model of the game
     */
    explicit View(Stratego& model);

    /*!
     * @brief ask Placement Pieces
     */
    void askPlacementPieces();

    /*!
     * @brief Show the interactive placement welcome and the piece
     * @param Blue the blue piece
     * @param Red the red piece
     */
    void interactivePlacement();


    /*!
     * @brief display Welcome
     */
    void displayWelcome();

    /*!
     * @brief ask Movement
     */
    void askMovement();

    /*!
     * @brief ask to Select Square
     */
    void askSelectSquare();

    /*!
     * @brief ask Row
     */
    void askRow();

    /*!
     * @brief askColumn
     */
    void askColumn();

    /*!
     * @brief display Error
     */
    void displayError();

    /*!
     * @brief askDeselectSquare
     */
    void askDeselectSquare();

    /*!
     * @brief ask Mode Choice
     */
    void askGameModChoice();

    /*!
     * \brief ask Placement Position
     */
    void askPlacementPosition(const std::string & piece ,Color color);

    /*!
     * \brief showErrorSelection
     */
    void showErrorSelection();

    /*!
     * \brief displayTurnBoard
     */
    void displayTurnBoard();

    /*!
     * \brief show the Winner
     */
    void showWinner();

    /*!
     * \brief ask to the current player the position where to place a given piece
     * \param piece the given piece to place
     * \param color the color of the current player
     */
    void askPlacementPosition(const Piece & piece ,const Color color);

    /*!
     * \brief show to the current player an error of placement
     * \param color the color of the player
     */
    void showErrorPlacement(Color color);


private:

    void showBoardBeginner(Color color);
    void showBoardNormal(Color color);
    void update(const nvs::Subject *subject) override;
};

}
#endif // VIEW_H
