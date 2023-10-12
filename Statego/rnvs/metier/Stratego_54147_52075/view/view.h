#ifndef VIEW_H
#define VIEW_H

#include "utils/observer.h"
// #include "model/stratego.h"  // rnvs : include / déclaration anticipée
#include <string>               // rnvs : include / déclaration anticipée

namespace stratego
{

enum class
Color;           // rnvs : include / déclaration anticipée
class Stratego;             // rnvs : include / déclaration anticipée

// class Subject;           // rnvs : include / déclaration anticipée

class View : public nvs::Observer
{

  private :
    stratego::Stratego & model_ ;

  public:

    /*!
     * @brief Constructor of view.
     * @param model of the game
     */
    View(Stratego & model);

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
    void askModChoice();

    /*!
     * @brief ask Placement Position
     */
    void askPlacementPosition(std::string, Color);

  private:

    void showBoardBeginner(Color color);
    void showBoardNormal(Color color);
    void update(const nvs::Subject * subject) override;
};

}
#endif // VIEW_H
