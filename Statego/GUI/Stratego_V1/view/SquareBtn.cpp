#include "SquareBtn.h"

namespace stratego{

SquareBtn::SquareBtn(QPushButton *parent, int x, int y, QString value)
    : QPushButton{parent}, x_{x},y_{y},value_{value}{


}

void SquareBtn::setValue(QString value)
{
    this->setText(value);
    this->value_ = value;
}

void SquareBtn::showPosition()
{
    qDebug() << "x : " << x_ << " y : " << y_ << " value : " << value_;
}

Position SquareBtn::getPosition() const{
    return Position(x_,y_);
}

}

