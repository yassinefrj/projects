#ifndef SQUARE_H
#define SQUARE_H
#include <optional>
#include "square_type.h"
#include "piece.h"

namespace stratego{

class Square{

    Square_type typeCase_;

    std::optional<Piece> piece_;

public:
    /*!
     * @brief Construct a Square with a type, an optional piece and a position
     * @param typeCase the type of the sqaure
     * @param piece the piece to place in
     */
    Square(Square_type typeCase =Square_type::EARTH,
           std::optional<Piece> piece = std::nullopt);

    /*!
     * @brief get the piece
     * @return the piece
     */
    std::optional<Piece>& getPiece() ;

    /*!
     * @brief set the piece
     * @return the piece
     */
    void setPiece(std::optional<Piece> piece);

    /*!
     * @brief set a square type
     * @param type of the square
     */
    void setSquareType(Square_type type);

    /*!
     * @brief check if the type square is Land
     * @return true if the type square is Land
     */
    bool isLand() const;

    /*!
     * @brief check if the square if free
     * @return true if there's not Piece in
     */
    bool isFree() const;

    /*!
     * @brief check if the piece at the current square have the same color that the given color
     * @param the color to compare
     * @return true if the colors are the same
     */
    bool isSameColor(Color& color);

    /*!
     * @brief Remove the piece of the current square
     */
    void removePiece();

};
/*!
 * @brief redifine of operator <<
 * @param os the output
 * @param dt the input
 * @return the redifinition of operator <<
 */
std::ostream& operator<<(std::ostream& os, const Square& dt);
}
#endif // SQUARE_H
