#ifndef STATE_H
#define STATE_H

namespace stratego {

/*!
 * @brief The State enum used to know the state of stratego game
 */
enum class State {
    NOT_STARTED,INTERACTIVE_PLACEMENT,IN_GAME_BEGINNER,IN_GAME_NORMAL,
    PIECE_NOT_SELECTED,PIECE_SELECTED,TURN_PLAYED,
    GAME_OVER
};

}

#endif // STATE_H
