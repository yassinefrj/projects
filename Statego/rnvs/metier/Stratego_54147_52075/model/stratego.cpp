#include "stratego.h"

#include <iostream>     // rnvs : ajout

namespace stratego
{

Stratego::Stratego() : state_{State::NOT_STARTED}, currentPlayer_{0}
{
    this->players_[0].setColor(Color::RED);
    this->players_[1].setColor(Color::BLUE);
    this->board_ = Board();
}

void Stratego::startStratego(Difficulty difficulty)
{
    if (this->state_ != State::NOT_STARTED)
    {
        throw std::invalid_argument("This game state is not expected ! ");
    }
    else
    {
        switch (difficulty)
        {
            case Difficulty::BEGINNER:
                this->state_ = State::IN_GAME_BEGINNER;
                this->difficulty_ = Difficulty::BEGINNER;
                notifyObservers();
                break;
            case Difficulty::NORMAL:
                this->state_ = State::IN_GAME_NORMAL;
                this->difficulty_ = Difficulty::NORMAL;
                // break;   // rnvs : comm
                notifyObservers();
        }

    }

}

bool Stratego::isSelectionExact(const Position & pos)
{
    Color currentPlayerColor = this->players_[currentPlayer_].getColor();
    if (board_.isInside(pos) &&
            board_.isLand(pos) &&
            !board_.isFreeSquare(pos) &&
            board_.isSameColor(pos, currentPlayerColor) &&
            board_.getPiece(pos)->getLevel() != 0 &&
            board_.getPiece(pos)->getLevel() != 11)
    {
        this->selected_ = pos;
        return true;
    }
    else
    {
        this->state_ = State::PIECE_NOT_SELECTED;
        notifyObservers();
    }

    return false;

}

void Stratego::selectPiece(const Position & pos)
{

    if (isSelectionExact(pos))
    {
        this->state_ = State::PIECE_SELECTED;
        notifyObservers();
    }


}

void Stratego::addPiece(const Position & pos, Piece piece)
{
    if (state_ == State::NOT_STARTED || state_ == State::PIECE_SELECTED)
    {
        this->board_.addPiece(pos, piece);
    }
}

void Stratego::attack(const Position & pos)
{
    if (this->state_ != State::PIECE_SELECTED)
    {
        throw std::invalid_argument("This game state is not expected ! ");
    }

    if ((board_.getPiece(this->selected_)->getLevel() == 1
            && board_.getPiece(pos)->getLevel() == 10)
            || (board_.getPiece(this->selected_)->getLevel() == 3
                && board_.getPiece(pos)->getLevel() == 11))
    {

        Piece win = board_.getSquare(this->selected_).getPiece().value();
        Piece dead = board_.getSquare(pos).getPiece().value();
        this->deadPieces_.push_back(dead);
        this->board_.removePiece(pos);
        win.setVisible(true);
        turnPlayed();

    }
    else
    {

        if (board_.getPiece(selected_).value().isSameLevel(board_.getPiece(
                    pos).value()))
        {

            this->deadPieces_.push_back(board_.getPiece(selected_).value());
            this->deadPieces_.push_back(board_.getPiece(pos).value());
            this->board_.removePiece(pos);
            this->board_.removePiece(this->selected_);
            turnPlayed();

        }
        else if (board_.getPiece(selected_).value().isStronger(
                     board_.getPiece(pos).value()))
        {

            Piece win = board_.getSquare(this->selected_).getPiece().value();
            Piece dead = board_.getSquare(pos).getPiece().value();
            this->deadPieces_.push_back(dead);
            this->board_.removePiece(pos);
            win.setVisible(true);
            turnPlayed();

        }
        else
        {
            Piece dead = board_.getSquare(this->selected_).getPiece().value();
            this->deadPieces_.push_back(dead);
            this->board_.removePiece(this->selected_);
            this->board_.getPiece(pos)->setVisible(true);
            turnPlayed();
        }
    }

}

void Stratego::movePieceNormal(const Position & pos)
{
    if (this->state_ != State::PIECE_SELECTED)
    {
        throw std::invalid_argument("This game state is not expected ! ");
    }
    if (squareInsideLand(pos) )
    {
        if ((this->selected_.x() + 1 == pos.x() ) ||
                (this->selected_.x() - 1 == pos.x() ) ||
                (this->selected_.y() + 1 == pos.y() ) ||
                (this->selected_.y() - 1 == pos.y()))
        {
            if (board_.getPiece(pos)->getColor() !=
                    players_[currentPlayer_].getColor() &&
                    board_.getPiece(pos) != std::nullopt)
            {
                attack(pos);
            }
            else if (board_.getPiece(pos)->getColor() ==
                     players_[currentPlayer_].getColor() &&
                     board_.getPiece(pos) != std::nullopt)
            {
                this->state_ = State::PIECE_NOT_SELECTED;
                notifyObservers();
            }
            else
            {
                Piece p = board_.getSquare(this->selected_).getPiece().value();
                this->board_.addPiece(pos, p);
                this->board_.removePiece(this->selected_);
                turnPlayed();
            }
        }
        else
        {
            this->state_ = State::PIECE_NOT_SELECTED;
            notifyObservers();
        }
    }
    else
    {
        state_ = State::PIECE_SELECTED;
        notifyObservers();
    }
}

void Stratego::movePieceScout(const Position & pos)
{
    if (this->state_ != State::PIECE_SELECTED)
    {
        throw std::invalid_argument("This game state is not expected ! ");
    }

    int  top {0};
    int bottom {0};
    int left {0};
    int right{0};

    if (this->selected_.x() > pos.x() )
    {
        top = 1;
    }
    else if (this->selected_.x() < pos.x() )
    {
        bottom = 1;
    }
    else if (this->selected_.y() < pos.y() )
    {
        right = 1;
    }
    else if (this->selected_.y() > pos.y() )
    {
        left = 1;
    }

    Square squareStart = this->board_.getSquare(this->selected_);
    Position posStart = this->selected_;
    bool isFree{true};

    while (!(posStart == pos) )
    {
        posStart.x(posStart.x() + bottom);
        posStart.x(posStart.x() - top);
        posStart.y(posStart.y() - left);
        posStart.y(posStart.y() + right);
        squareStart = this->board_.getSquare(posStart);
        if (!squareStart.isLand() || !squareStart.isFree())
        {
            isFree = false;
            break;
        }
    }

    if (isFree)
    {
        Piece p = board_.getSquare(this->selected_).getPiece().value();
        this->board_.addPiece(pos, p);
        this->board_.removePiece(this->selected_);
        turnPlayed();
    }
    else if (this->board_.getPiece(posStart)->getColor()
             != board_.getPiece(selected_)->getColor())
    {
        if (!(posStart == pos) )
        {
            state_ = State::PIECE_NOT_SELECTED;
            notifyObservers();
        }
        else
        {
            attack(posStart);
        }
    }
    else
    {
        state_ = State::PIECE_NOT_SELECTED;
        notifyObservers();
    }

}

void Stratego::movePiece(const Position & pos)
{
    int pieceStep = this->board_.getPiece(this->selected_)->getStep();
    switch (pieceStep)
    {
        case -1 :
            if (isMoveScoutExact(this->selected_, pos))
            {
                movePieceScout(pos);
            }
            else
            {
                this->state_ = State::PIECE_NOT_SELECTED;
                notifyObservers();
            }
            break;
        case 1 :
            movePieceNormal(pos);
            break;

    }

}

Board Stratego::getBoard() const
{

    //Bien faire attention au etats.
    return this->board_;
}

State Stratego::getState() const
{
    return this->state_;
}

bool Stratego::isFinish()
{
    for (int i{0}; i < static_cast<int>(deadPieces_.size()); i++)
    {
        if (deadPieces_.at(i).getLevel() == 0 &&
                deadPieces_.at(i).getColor() == Color::BLUE)
        {
            this->currentPlayer_ = 1;
            state_ = State::GAME_OVER;
            notifyObservers();
            return true;
        }
        else if ( deadPieces_.at(i).getLevel() == 0 &&
                  deadPieces_.at(i).getColor() == Color::RED)
        {
            this->currentPlayer_ = 0;
            state_ = State::GAME_OVER;
            notifyObservers();
            return true;
        }
    }

    int deadBlueMovable{0};
    int deadRedMovable{0};
    for (int i{0}; i < static_cast<int>(deadPieces_.size()); i++)
    {
        if (deadPieces_.at(i).getLevel() != 0 &&
                deadPieces_.at(i).getLevel() != 11)
        {
            if (deadPieces_.at(i).getColor() == Color::BLUE)
            {
                deadBlueMovable++;
            }
            else
            {
                deadRedMovable++;
            }
        }
    }

    if (deadBlueMovable == 33 )
    {
        this->currentPlayer_ = 1;
        state_ = State::GAME_OVER;
        notifyObservers();
        return true;
    }
    else if (deadRedMovable == 33)
    {
        this->currentPlayer_ = 0;
        state_ = State::GAME_OVER;
        notifyObservers();
        return true;
    }

    return false;
}

bool Stratego::isFullCorrectly()
{
    int nbPieces = 0;
    for (int i{0} ; i < 10; i++)
    {
        for (int j{0}; j < 10 ; j++)
        {
            if (this->board_.getPiece(Position(i, j)) != std::nullopt)
            {
                nbPieces++;
            }
        }
    }
    return nbPieces == 80;

}

Color Stratego::getCurrentPlayerColor() const
{

    return this->players_[currentPlayer_].getColor();
}

Difficulty Stratego::getDifficulty() const
{
    if (this->state_ == State::NOT_STARTED )
    {
        throw std::invalid_argument("This game state is not expected ! ");
    }
    return this->difficulty_;
}

void Stratego::turnPlayed()
{
    if (state_ != State::PIECE_SELECTED)
    {
        throw std::invalid_argument("This game state is not expected !  Turn");
    }
    else
    {
        this->state_ = State::TURN_PLAYED;
        switchPlayer();
        notifyObservers();
    }

}

void Stratego::interactivePlacement()
{
    // rnvs : pas de placement sur le Board dans ce qui suit : ko
    if (state_ != State::NOT_STARTED)
    {
        throw std::invalid_argument("This game state is not expected ! ");
    }
    else
    {
        clearBoard();
    }

    for (int i {0}; i < 12; i++)
    {
        if (i == 2)
        {
            // rnvs : éclaireur
            interactiveBlue.push_back(Piece(i, Color::BLUE));

        }
        else if (i == 11)
        {
            // rnvs : drapeau ou bombe ?
            interactiveBlue.push_back(Piece(i, Color::BLUE, 0));
        }
        else
        {
            interactiveBlue.push_back(Piece(i, Color::BLUE, 1));
        }

    }

    for (int i {0}; i < 12; i++)
    {
        if (i == 2)
        {
            interactiveRed.push_back(Piece(i, Color::RED));

        }
        else if (i == 11)
        {
            interactiveRed.push_back(Piece(i, Color::RED, 0));
        }
        else
        {
            interactiveRed.push_back(Piece(i, Color::RED, 1));
        }

    }
}

std::vector<Piece> Stratego::getInteractiveBlue() const
{
    return interactiveBlue;
}
std::vector<Piece> Stratego::getInteractiveRed() const
{
    return interactiveRed;
}


bool Stratego::squareInsideLand(const Position & pos)
{
    return board_.isInside(pos) &&  board_.isLand(pos);
}

bool Stratego::isMoveScoutExact(const Position & start,
                                const Position & end)
{
    return (start.x() > end.x() && start.y() == end.y())
           || (start.x() < end.x() && start.y() == end.y())
           || (start.y() < end.y() && start.x() == end.x())
           || (start.y() > end.y() && start.x() == end.x());

}

void Stratego::switchPlayer()
{
    std::cout << "ok " << std::endl;
    if (this->state_ != State::TURN_PLAYED)
    {
        throw std::invalid_argument("This game state is not expected ! ");
    }
    else
    {
        if (this->currentPlayer_ == 0)
        {
            currentPlayer_ = 1;
        }
        else
        {
            currentPlayer_ = 0;
        }
    }
}


void Stratego::clearBoard()
{
    for (int i{0};  i < 10; i++)
    {
        for (int j{0}; j < 10; j++)
        {
            this->board_.removePiece(Position(i, j));
        }
    }
}

}
