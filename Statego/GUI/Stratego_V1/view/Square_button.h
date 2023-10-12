#ifndef SQUARE_BUTTON_H
#define SQUARE_BUTTON_H
#include <QPushButton>

namespace stratego{

class SquareBtn : public QPushButton{

    int x_;
    int y_;
    QString pieceValue_;

public :
    explicit SquareBtn(QWidget *parent = 0,int x = 0,int y = 0, QString value = nullptr);
private slots :
    void showPosition();
};



}
#endif // SQUARE_BUTTON_H
