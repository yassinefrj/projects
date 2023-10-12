#ifndef BOARD_H
#define BOARD_H
#include <array>
#include "square.h"
#include "position.h"
namespace stratego {

class Board{
    std::array<std::array<Square,10>,10> board_;

public:

    /*!
     * \brief Construct a board of 10x10 empty Square
     */
    Board();


    /*!
     * @brief getBoard
     * @return the board
     */
    std::array<std::array<Square,10>,10> getBoard() const;

    /*!
     * @brief getSquare
     * @param pos the position of the square in the board
     * @return a square
     */
    Square getSquare(const Position& pos) const;

    /*!
     * @brief Check if given position is inside the board
     * @param pos the position to check
     * @return true if the position is inside the board
     */
    bool isInside(const Position& pos);

    /*!
     * @brief Check if the square at the given position have the same color that the given color
     * @param pos the position to check
     * @param color the color to check
     * @return True if colors are the same
     */
    bool isSameColor(const Position& pos,Color color);

    /*!
     * @brief Check if the square at the given position is free
     * @param pos the position to check
     * @return true if the position is free
     */
    bool isFreeSquare(const Position& pos);

    /*!
     * @brief Add a piece at the given position
     * @param pos the position to add
     * @param piece the piece to add
     */
    void addPiece(const Position& pos,Piece piece);

    /*!
     * @brief Remove a piece at the given position
     * @param the position where to remove
     */
    void removePiece(const Position& pos);

    /*!
     * @brief Check if the square at the given position is of type LAND
     * @param the positon where to check
     * @return true if the squ
     */
    bool isLand(const Position& pos);

    /*!
     * @brief Get a Piece at the given position
     * @param the position where get the piece
     * @return the piece at the given position
     */
    std::optional<Piece>& getPiece(const Position& pos);

};

}

#endif // BOARD_H
