#include "controller/controller.h"
#include "view/view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    stratego::Stratego game{};
    stratego::View view{};
    stratego::Controller ctrl{game,view};
    return a.exec();
}
