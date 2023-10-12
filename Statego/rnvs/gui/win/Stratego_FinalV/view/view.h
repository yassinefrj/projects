#ifndef VIEW_H
#define VIEW_H
#include "model/difficulty.h"
#include "model/position.h"
#include "qpushbutton.h"
#include "utils/observer.h"
#include "model/color.h"
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>

namespace Ui
{
class View;
}

namespace stratego
{
class Controller;
}


namespace stratego{

class View : public QMainWindow , public nvs::Observer{

    Q_OBJECT

public:
    /*!
     * \brief controller_ the controller
     */
    Controller* controller_ = nullptr;

    /*!
     * \brief View Initialize the view with some default values.
     * \param parent in stratego game, this view has no parent.
     */
    explicit View(QWidget *parent = nullptr);
    ~View();
    void setCtrl( Controller * ctrl);
    /*!
     * \brief showBoardNormal show the grid game board for the beginner mode to the given player color
     * \param color the given player color
     */
    void showBoard(const Color& playerColor);
    /*!
     * \brief showBoardBeginner show the grid game board for the beginner mode to the given player color
     * \param playerColor the given player color
     */
    /*!
     * \brief clearGameBoard clear the grid of the game board
     */
    void clearGameBoard();
    /*!
     * \brief clearInteractivesBoards clear the selecting AND putting board, used in the interactiv mode
     */
    void clearInteractivesBoards();


private slots:

    /*!
     * \brief on_menuChoice_activated when a difficulty is choice, update the "difficulty" attribute, by default 0.
     * \param index the index of the selected difficulty
     */
    void on_menuChoice_activated(int index);


    /*!
     * \brief on_file_start_clicked read 2 files(.txt) and start the game
     */
    void on_file_start_clicked();

    /*!
     * \brief on_interactive_start_clicked start the interactive mode by clearing the selecting AND putting board, then initialize them.
     */
    void on_interactive_start_clicked();

    /*!
     * \brief on_actionNouvelle_Partie_triggered slot for the click on "Nouvelle Partie", quit the game and come back at the principal page
     * 0 = Principal page
     * 1 = Game
     * 2 = Interactive
     */
    void on_actionNouvelle_Partie_triggered();

    void on_actionManuel_triggered();

private:
    Ui::View * ui;

    int difficulty{0};//0 is beginner ,...
    /*!
     * \brief pathBlue the path of the blue piece file
     */
    std::string pathBlue;
    /*!
     * \brief pathRed the path of the red piece file
     */
    std::string pathRed;
    /*!
     * \brief saveIcon_ save the selected Icon
     */
    QIcon saveIcon_;
    /*!
     * \brief tmp used to put saveIcon_ at null
     */
    QIcon tmp;
    /*!
     * \brief saveLevel_ save the selected level
     */
    int saveLevel_;
    /*!
     * \brief saveNbStep_ save the selected NbStep
     */
    int saveNbStep_;
    /*!
     * \brief saveColor_ save the selected color
     */
    Color saveColor_;
    /*!
     * \brief nbPuttingOfPiece compute the number of piece putted in the board, may stop at value 80
     */
    int nbPuttingOfPiece_ ;
    /*!
     * \brief isPutted check if a Piece is putted in the interativ putting board
     */
    bool isPutted_;
    /*!
     * \brief secondJoueur true when the first player has finish to full his board.
     */
    bool secondPlayerTurn_;
    /*!
     * \brief update, update the view according to the current game state
     * \param subject not used because the FX view and the Console view are totally different in our code
     */
    void update(const nvs::Subject *subject) override;
    /*!
     * \brief addIconsBtnsInteractiv set a Icon to the given button and put the given button in the interactive selection Board
     * \param button the button where to add a icon and to add in the board game
     * \param pos the pos of the board game where to add the given button
     * \param level the level of the button
     */
    void addIconsBtns(QPushButton* button,const Position& pos,int level,QGridLayout* grid);
    /*!
     * \brief showBoardInteractiv show the interactive putting board used by both players
     */
    void showInteractivPuttingBoard();
    /*!
     * \brief showSecondInteractivBoard show interactive selected board for the secund player
     */
    void showSecondInteractivBoard();

    void showInteractivSelectBoard(int rowStart,const Color& color);
    /*!
     * \brief showInformations show the given player color game informations
     * \param color the given player color
     */
    void showInformations(Color color);
    /*!
     * \brief showWinner show the winner (the current is who loose)
     */
    void showWinner();
    /*!
     * \brief showLastKilledPiece show the last Blue and Red killed piece
     */
    void showLastKilledPiece();
    /*!
     * \brief getIcon get the Icon associated with a given level
     * \param level the given level
     * \return the Icon associated with the given level
     */
    QIcon getIcon(int level);
    /*!
     * \brief showSelectedPieceInformations show the informations of the selected Piece
     */
    void showSelectedPieceInformations();
    /*!
     * \brief getName get the name of a piece
     * \param level the level of the piece
     * \return the corresponding name
     */
    QString getName(int level);

    void messageSelection();
};

}
#endif // VIEW_H
