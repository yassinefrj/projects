#include "view.h"
#include "controller/controller.h"
#include "ui_view.h"
#include "menu.h"
#include "SquareBtn.h"
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

namespace stratego {
stratego::View::View( QWidget *parent)
    : QMainWindow(parent),ui(new Ui::View){
    ui->setupUi(this);
    this->show();

}

void View::setCtrl(Controller * ctrl){
    controller_ = ctrl;
}

stratego::View::~View(){
    delete ui;
}


void View::clearBoard()
{

    while ( QLayoutItem* item = ui->gridLayout->layout()->takeAt( 0 ) )
    {
        Q_ASSERT( ! item->layout() );
        delete item->widget();
        delete item;
    }
}


void View::showBoard(){
    clearBoard();

    for (int row {0} ; row < 10 ; row++ ) {
        for(int column{0}; column < 10 ; column++){
            stratego::Position pos(row,column);
            if(controller_->getGame().getBoard().getSquare(pos).getPiece() != std::nullopt) {
                int a =  controller_->getGame().getBoard().getPiece(pos)->getLevel();
                QString b = QString::number(a);
                stratego::SquareBtn * button = new stratego::SquareBtn(nullptr,row,column,b);

                if(controller_->getGame().getBoard().getPiece(pos)->getColor() == stratego::Color::BLUE){
                    button->setStyleSheet("color: black;"
                                          "background-color: blue;");
                }else{
                    button->setStyleSheet("color: black;"
                                          "background-color: red;");
                }
                button->setValue(b);
                this->ui->gridLayout->addWidget(button,row,column);

                connect(button,  &QPushButton::clicked,this, [&, this, pos]() {
                    this->controller_->clickSquare(pos);
                }
                );


            }else{
                if (controller_->getGame().getBoard().getSquare(pos).isLand()){
                    SquareBtn* btLand = new stratego::SquareBtn(nullptr,row,column);

                    btLand->setValue("");
                    this->ui->gridLayout->addWidget(btLand,row,column);
                    connect(btLand,  &QPushButton::clicked,this, [&, this, pos]() {
                        this->controller_->clickSquare(pos);
                    }
                    );
                }else{
                    SquareBtn* btWater = new stratego::SquareBtn(nullptr,row,column,"W");
                    btWater->setEnabled(false);
                    btWater->setStyleSheet("background-color: cyan;");
                    btWater->setValue("W");
                    this->ui->gridLayout->addWidget(btWater,row,column);

                }
            }
        }
    }
}



void stratego::View::update(const nvs::Subject *subject){

    switch (this->controller_->getGame().getState()) {
    case State::NOT_STARTED:
        break;
    case State::INTERACTIVE_PLACEMENT:
        break;
    case State::IN_GAME_NORMAL:{
        QString textStatus = "Au tour du joueur courant";
        ui->infos->setText(textStatus);
        std::cout<< "In game normal " << std::endl;
        showBoard();
        break;
    }
    case State::IN_GAME_BEGINNER:
        std::cout<< "In game beginner " << std::endl;
        showBoard();
        break;
    case State::PIECE_NOT_SELECTED:
        std::cout<< "Choississez une piece correcte " << std::endl;
        ui->infos->setText("Statut : Sélectionnez un pion vous appartenant et déplacable"  );
        showBoard();
        break;
    case State::PIECE_SELECTED:
        std::cout<< "Piece Selectionnez faite un move permits  " << std::endl;
          ui->infos->setText("Statut : Sélectionnez une case ou déplacer votre pion"  );
        showBoard();
        break;
    case State::TURN_PLAYED:
         ui->infos->setText("Statut : Joueur Suivant..."  );
        showBoard();
        break;
    case State::GAME_OVER:
          ui->infos->setText("Statut : FIN DE PARTIE"  );
        std::cout<< "FIN DE PARTIE " << std::endl;
         ui->stackedWidget->setCurrentIndex(0);
        break;
    }

}


void View::on_comboBox_4_activated(int index)
{
    if(index==0){
        this->difficulty = 0;
    }else{
        this->difficulty = 1;
    }
}


void View::on_blueBtn_4_clicked()
{
    QString filter = "Fichier Texte (*.txt) ";
    QString file_name =  QFileDialog::getOpenFileName(this,"Ouvrez le fichier des pions bleus","../Stratego_V1",filter);
    QFile file(file_name) ;

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Erreur","Fichier non ouvert !");
    }else{
        QTextStream in (&file);
        QString text = in.readAll();
        this->pathBlue= file_name.toStdString();
    }
    file.close();

}


void View::on_redBtn_4_clicked()
{
    QString filter = "Fichier Texte (*.txt) ";
    QString file_name =  QFileDialog::getOpenFileName(this,"Ouvrez le fichier des pions rouges ","../Stratego_V1",filter);
    QFile file(file_name) ;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Erreur","Fichier non ouvert !");
    }else{
        QTextStream in (&file);
        QString text = in.readAll();
        this->pathRed = file_name.toStdString();
    }

    file.close();

}


void View::on_pushButton_clicked()
{
    std::cout << this->pathBlue << std::endl;
    std::cout << this->pathRed << std::endl;
    controller_->startGame(difficulty,this->pathBlue,this->pathRed);
    ui->stackedWidget->setCurrentIndex(1);
}





}
