#ifndef PIECE_H
#define PIECE_H
#include "color.h"
//#include <iostream>   // rnvs : include / déclaration anticipée
#include <ostream>      // rnvs : include / déclaration anticipée


namespace stratego
{

class Piece
{

    Color color_;

    int level_;

    int nbStepMax_;

    bool isVisible_ {false};

  public:

    /*!
     * @brief Construct a Piece with a level, a color
     * @param level of the piece
     * @param color of the piece
     */
    Piece(int level, Color color);

    /*!
     * @brief Construct a Piece with a level, color, a number of step
     * @param level of the piece
     * @param color of the piece
     * @param nbStepMax of the piece
     */
    Piece(int level, Color color, int nbStepMax);

    /*!
     * @brief get the level of the piece
     * @return the level of the piece
     */
    int getLevel() const;

    /*!
     * @brief get the color of the piece
     * @return the color of the piece
     */
    Color getColor() const;

    /*!
     * @brief get the number of step of the piece
     * @return the number of step of the piece
     */
    int getStep() const;

    /*!
     * @brief get the visibility of the piece (used in beginner mode)
     * @return the visibility of the piece
     */
    bool isVisible() const;

    /*!
     * @brief set the visibilité of the piece (used in beginner mode)
     * @param the visibility
     */
    void setVisible(bool isVisible);

    /*!
     * @brief check if the level of the piece is the same that the given level
     * @param the given piece to compare the level
     * @return true if levels are the same
     */
    bool isSameLevel(const Piece & piece);

    /*!
     * @brief check if the level of the piece is stronger that the given piece
     * @param the given piece to compare the level
     * @return true if the current piece is stronger that the given
     */
    bool isStronger(const Piece & piece);
};

std::ostream & operator<<(std::ostream & os, const Piece & dt);

}

#endif // PIECE_H
