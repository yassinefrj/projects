#include "Square_button.h"
#include <QDebug>

stratego::SquareBtn::SquareBtn(QWidget *parent,int x, int y, QString value)
    : QPushButton(parent), x_{x},y_{y},pieceValue_{value}
{
    this->setText(value);
    QObject::connect(this,&QPushButton::clicked,[&](){
        this->showPosition();
    });

}

void stratego::SquareBtn::showPosition(){
 qDebug() << "x : " << x_ << " y : " << y_ << " value : " << pieceValue_;
}
