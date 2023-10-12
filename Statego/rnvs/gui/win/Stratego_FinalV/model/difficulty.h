#ifndef DIFFICULTY_H
#define DIFFICULTY_H
#include <iostream>

namespace stratego{

/*!
 * @brief Enum Difficulty for the difficulty of Stratego games
 */
enum class Difficulty{
    BEGINNER,NORMAL
};

std::ostream& operator<<(std::ostream& os, const Difficulty& dt);


}

#endif // DIFFICULTY_H
