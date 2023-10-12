#ifndef CONTROLLER_H
#define CONTROLLER_H
// #include "model/stratego.h"  // rnvs : include / déclaration anticipée
// #include "view/view.h"       // rnvs : include / déclaration anticipée
// #include "utils/file_reader.h"   // rnvs : include / déclaration anticipée
// #include "utils/keyboard.hpp"    // rnvs : include / déclaration anticipée
// #include "utils/string_convert.hpp"  // rnvs : include / déclaration anticipée

namespace stratego
{

class Stratego;     // rnvs : include / déclaration anticipée
class View;         // rnvs : include / déclaration anticipée
class Position;     // rnvs : include / déclaration anticipée
enum class Difficulty;  // rnvs : include / déclaration anticipée

class Controller
{
    Stratego & game_;
    View & view_;

  public:

    /*!
     * @brief Construct a controller for the Stratego game
     * @param game game
     * @param view view of the game
     */
    Controller(Stratego & game, View & view);

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
     * @brief Do the interactive Placement
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
};

}

#endif // CONTROLLER_H
