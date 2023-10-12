#ifndef STRATEGO_H
#define STRATEGO_H
#include <vector>
#include "utils/subject.h"
#include "difficulty.h"
#include "state.h"
#include "position.h"
#include "board.h"
#include "player.h"
#include <QDebug>


namespace stratego {

class Stratego : public nvs::Subject{
    Difficulty difficulty_;
    State state_;
    Board board_;
    int currentPlayer_;
    Position selected_;
    std::array<Player,2> players_;
    std::vector<Piece> deadPieces_;
    std::vector<Piece> interactiveBlue;
    std::vector<Piece> interactiveRed;


public:
    /*!
     * @brief Construct a Stratego game
     */
    Stratego();

    /*!
     * @brief Set the state at IN_GAME and set the difficulty
     */
    void startStratego(const Difficulty& difficulty);

    /*!
     * \brief startInteractivPlacemement Update the state for the interactiv placement
     * \param difficulty the difficulty of the game
     */
    void startInteractivPlacemement(const Difficulty& difficulty);

    /*!
     * @brief select a piece at the given position
     * @param the position to select
     */
    void selectPiece(const Position& pos);

    /*!
     * @brief add a given piece in the board at the given position
     * @param pos the position to put
     * @param piece the piece to put
     */
    void addPiece(const Position& pos,Piece piece);
// Check si pas mieux de mettre un std optionnal

    /*!
     * @brief move a piece at the given position
     * @param pos the positon where to move
     */
    void movePiece(const Position& pos);

    /*!
     * \brief getSelected get the position of the selected piece
     * \return the position of the selected piece
     */
    Position getSelected();

    /*!
     * @brief get the board
     * @return the board of the game
     */
    Board getBoard() const;

    /*!
     * @brief get the state
     * @return the state of the game
     */
    State getState() const;

    /*!
     * \brief getDeadPiece get the vector of deadPieces;
     * \return the vector of dead Piece
     */
    std::vector<Piece>& getDeadPiece();

    /*!
     * @brief Check if the game is finish
     * @return true if the game is finish
     */
    bool isFinish()  ;

    /*!
     * @brief check if the board is full of piece (except the middle)
     * @return true if the board is full of piece
     */
    bool isFullCorrectly() ;

    /*!
     * @brief get the Color of the current player
     * @return the color of the current player
     */
    Color getCurrentPlayerColor() const;

    /*!
     * \brief getDifficulty get the difficulty of the game
     * \return the difficulty of the game
     */
    Difficulty getDifficulty() const;

    /*!
     * @brief turn the players
     */
    void turnPlayed();

    /*!
     * @brief do the interactive place placement
     * @param Blue the blue pieces available
     * @param Red the red pieces available
     */
    void interactivePlacement();

    /*!
     * \brief get the list of blue piece for interactive placement
     * \return the list of blue piece
     */
    std::vector<Piece> getInteractiveBlue() const ;

    /*!
     * \brief get the list of red piece for interactive placement
     * \return
     */
    std::vector<Piece> getInteractiveRed() const ;

    /*!
     * \brief Check if the board is full of piece (has 80 pieces)
     * \return true if the board is full
     */
    bool isFull() const;

    /*!
     * \brief Switch the player for the interactive placement
     */
    void nextPlayerPlacement();

    /*!
     * \brief quitGame Clear the board and update the states & view
     */
    void quitGame();



private :

    /*!
     * \brief do a move for the scout piece
     * \param pos the end position
     */
    void movePieceScout(const Position& pos);

    /*!
     * \brief do a move for a normal piece
     * \param pos the end position
     */
    void movePieceNormal(const Position& pos);

    /*!
     * @brief Check If the selection is possible
     * @param pos
     * @return
     */
    bool isSelectionExact(const Position& pos);

    /*!
     * @brief Check If the selection is Inside the board and a Land
     * @param pos
     * @return
     */
    bool squareInsideLand(const Position& pos);

    /*!
     * @brief Do the attack to the given position
     * @param pos the given position
     */
    void attack(const Position& pos);

    /*!
     * @brief Check if the move is possible for the piece "Scout"
     * @param start the start position
     * @param posEnd the end position
     * @return true is the move is possible
     */
    bool isMoveScoutExact(const Position& start,const Position& posEnd);

    /*!
     * @brief switch the current player
     */
    void switchPlayer();

    /*!
     * @brief clear the the piece from the Board
     */
    void clearBoard();
};

/*!
 * @brief operator <<
 * @param out
 * @param in
 * @return
 */
std::ostream & operator<<(std::ostream & out, const Stratego & in);


}


#endif // STRATEGO_H
