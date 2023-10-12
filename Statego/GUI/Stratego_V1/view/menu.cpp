#include "menu.h"


namespace stratego{

stratego::Menu::Menu()
{
    showMenu();
    this->setFixedSize(600,600);
}

void stratego::Menu::showMenu(){

    VBox = new QVBoxLayout;
    difficulty = new QComboBox;
    gameTitle = new QLabel("Stratego");


    gameTitle->setStyleSheet("color: white;"
                             "background-color: blue;");


    difficulty->addItem("Amateur");
    difficulty->addItem("Normal");

    VBox->addWidget(gameTitle);
    VBox->addWidget(difficulty);
    VBox->setAlignment(Qt::AlignHCenter);


    setLayout(VBox);
}


}
