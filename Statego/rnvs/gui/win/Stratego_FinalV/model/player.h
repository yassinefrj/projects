#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "color.h"

namespace stratego {

class Player{

    Color color_;

public:

    /*!
     * @brief The constructor of the player.
     * Initialize the color of the player.
     * @param color
     */
    Player(Color color=Color::RED);


    /*!
     * @brief Get the color of the player
     * @return
     */
    Color getColor() const;

    /*!
     * @brief setColor Set the color of the player
     */
    void setColor(Color color);

};

/*!
 * @brief redefinition of the << operator
 * @param out the output
 * @param in the input
 * @return the redifinition
 */
std::ostream & operator<<(std::ostream & out, const Player & pl);

}

#endif // PLAYER_H
