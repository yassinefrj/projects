#ifndef SQUAREBTN_H
#define SQUAREBTN_H
#include "model/stratego.h"
#include <QPushButton>
#include <QDebug>
namespace stratego{

class SquareBtn : public QPushButton{
    Q_OBJECT
private:
    int x_;
    int y_;
    QString value_;

public:
    explicit SquareBtn(QPushButton *parent,int x = 0,int y = 0, QString value = nullptr);
    /*!
     * \brief set the text of the button and the value of the attribute QString value_
     */
    void setValue(QString);
     stratego::Position getPosition() const;
private slots :
    void showPosition();

};
}
#endif // SQUAREBTN_H
