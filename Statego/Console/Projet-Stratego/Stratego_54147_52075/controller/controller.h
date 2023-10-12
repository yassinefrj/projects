#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model/stratego.h"
#include "view/view.h"
#include "utils/file_reader.h"
#include "utils/keyboard.hpp"
#include "utils/string_convert.hpp"

namespace stratego {

class Controller {
    Stratego& game_;
    View& view_;

public:

    /*!
     * @brief Construct a controller for the Stratego game
     * @param game game
     * @param view view of the game
     */
    Controller(Stratego& game, View& view);

    /*!
     * Starts the game
     */
    void start();
private:
    /*!
     * @brief Select a Piece
     */
    void selectPiece();
    /*!
     * @brief ask to the use a Position
     * @param minRow
     * @param maxRow
     * @return
     */
    void movePiece();
    /*!
     * @brief ask to the use a Position
     * @param minRow
     * @param maxRow
     * @return
     */
    Position askPosition();
    /*!
     * @brief Do the interactive Placement :
     * 1. Clear the board, Fill 2 vectors of pieces
     * 2. Show the cleared board
     * 3. Fill the board player by player and show the board at each step
     */
    void interactivePlacement();
    /*!
     * @brief Ask to the user wich configuration to use
     */
    void askConfigurationBoard();
    /*!
     * @brief Ask to the user if he's sure of it's choice
     */
    void askDeselectSquare();
    /*!
     * @brief Ask the difficulty
     */
    Difficulty askDifficulty();

    /*!
     * \brief ask a position to the user with 2 limits
     * \param rowMin the minimal row
     * \param rowMax the maximal row
     * \return
     */
    Position askPositionWithLimit(int rowMin, int rowMax);

};

}

#endif // CONTROLLER_H
