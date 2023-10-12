#ifndef POSITION_H
#define POSITION_H
// #include <string>        // rnvs : include / déclaration anticipée
// #include <ostream>       // rnvs : include / déclaration anticipée
namespace stratego
{

class Position
{

    int x_;
    int y_;

  public:

    /*!
     * @brief Construct a Position with a row and column
     * @param x
     * @param y
     */
    Position(int x = 0, int y = 0);

    /*!
     * @brief get the row value
     * @return the row value
     */
    int x() const;

    /*!
     * @brief get the column value
     * @return the column value
     */
    int y() const;

    /*!
     * @brief set the row value
     * @param x the row value
     */
    void x(int x);

    /*!
     * @brief set the column value
     * @param the column value
     */
    void y(int y);

    /*!
     * @brief redifine the == operator
     * @param pos the position to use
     * @return true is positions are the same
     */

    bool operator==(const Position & pos);

};


}



#endif // POSITION_H
