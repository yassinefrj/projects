#include "view.h"
#include "controller/controller.h"
#include "ui_view.h"
#include <QPushButton>
#include <QLabel>
#include <QGraphicsView>
#include <QFileDialog>
#include <QMessageBox>
#include <QColor>

namespace stratego {
stratego::View::View( QWidget *parent)
    : QMainWindow(parent),ui(new Ui::View){

    //Setup the view ui
    this->ui->setupUi(this);

    //Set the main window size
    this->setFixedSize(500,500);

    //Start the application at the first page
    this->ui->stackedWidget->setCurrentIndex(0);

    //Launch the view
    this->show();


}

void View::setCtrl(Controller * ctrl){
    controller_ = ctrl;
}

stratego::View::~View(){
    delete ui;
}

void stratego::View::update(const nvs::Subject *subject){
    //Color of the current player to show the appriopriate board.
    Color currentColor = this->controller_->getGame().getCurrentPlayerColor();

    //The actual state of the game
    State state = this->controller_->getGame().getState();

    switch (state) {
    case State::NOT_STARTED:
        break;
    case State::INTERACTIVE_PLACEMENT:
        break;
    case State::IN_GAME_NORMAL:{
        //Set the fixed in game window size
        this->setFixedSize(800,500);
        showBoard(currentColor);
        showInformations(currentColor);
        break;
    }
    case State::IN_GAME_BEGINNER:{
        this->setFixedSize(800,500);
        showBoard(currentColor);
        showInformations(currentColor);
        break;
    }
    case State::PIECE_NOT_SELECTED:
        messageSelection();
        showBoard(currentColor);
        break;
    case State::PIECE_SELECTED:
        showSelectedPieceInformations();
        showBoard(currentColor);
        break;
    case State::TURN_PLAYED:
        if(this->controller_->getGame().isFinish()){
            showWinner();
            showBoard(currentColor);
        }else{
            showInformations(currentColor);
            showBoard(currentColor);
        }
        break;
    case State::GAME_OVER:
        showWinner();

        break;
    case State::QUIT:{
        break;
    }
    }
}

void View::messageSelection(){
    this->ui->infosLiveLabel->setText("<strong>Choisissez une piece "
                                      "<br>vous appartenant<br> "
                                      "et"
                                      " déplacable</strong>");
}


void View::clearGameBoard(){
    while ( QLayoutItem* item = ui->game_G->layout()->takeAt( 0 ) ){
        Q_ASSERT( ! item->layout() );
        delete item->widget();
        delete item;
    }
    //Hide the last kill
    this->ui->lastKilledRed->setVisible(false);
    this->ui->lastKilledBlue->setVisible(false);
    this->ui->labelKilledPiece->setVisible(false);
}



const QSize btnSize = QSize(34, 34);

void View::showBoard(const Color& playerColor)
{
    //Configuration of the game grid.
    clearGameBoard();
    ui->game_G->setSpacing(0);
    showLastKilledPiece();

    for (int row {0} ; row < 10 ; row++ ) {
        for(int column{0}; column < 10 ; column++){

            stratego::Position pos(row,column);
            QString b = "";
            if(controller_->getGame().getBoard().getSquare(pos).getPiece() != std::nullopt) {
                QPushButton * button = new QPushButton();
                if(controller_->getGame().getBoard().getSquare(pos).getPiece()->getColor() == playerColor){
                    int a =  controller_->getGame().getBoard().getPiece(pos)->getLevel();
                    b = QString::number(a);
                    button->setText(b);
                    addIconsBtns(button,pos,a,this->ui->game_G);
                }else{
                    button->setFixedSize(btnSize);
                    this->ui->game_G->addWidget(button,pos.x(),pos.y());
                }


                //Checks if the piece is visible (Beginner mod).
                if(controller_->getGame().getBoard().getSquare(pos).getPiece()->isVisible()){
                    if(controller_->getGame().getDifficulty() == stratego::Difficulty::BEGINNER){
                        int a =  controller_->getGame().getBoard().getPiece(pos)->getLevel();
                        b = QString::number(a);
                        button->setText(b);
                        addIconsBtns(button,pos,a,this->ui->game_G);
                    }

                }

                //Set the color of the piece
                if(controller_->getGame().getBoard().getPiece(pos)->getColor() == stratego::Color::BLUE){
                    //Blue
                    button->setStyleSheet("color: white;"
                                          "background-color: blue;");
                } else{
                    //Red
                    button->setStyleSheet("color: white;"
                                          "background-color: #FF1717;");
                }


                // Illuminate green by piece selection.
                if(pos == this->controller_->getGame().getSelected()){
                    button->setStyleSheet("color: white;"
                                          "background-color: green;");
                }

                //click on a button.
                connect(button,  &QPushButton::clicked,this, [&, this, pos]() {
                    this->controller_->clickSquare(pos);
                }
                );

            }else{
                if (controller_->getGame().getBoard().getSquare(pos).isLand()){
                    QPushButton* btLand = new QPushButton();
                    btLand->setFixedSize(btnSize);
                    btLand->setStyleSheet("background-color : transparent");

                    this->ui->game_G->addWidget(btLand,row,column);
                    connect(btLand,  &QPushButton::clicked,this, [&, this, pos]() {
                        this->controller_->clickSquare(pos);});
                }else{
                    QPushButton* btWater = new QPushButton();
                    btWater->setVisible(false);
                    this->ui->game_G->addWidget(btWater,row,column);
                }
            }
        }
    }
}


void View::showInformations(Color color)
{
    this->ui->infosLiveLabel->setText("A votre tour");

    if(color == Color::RED){
        this->ui->titleInfos->setText("<strong>Rouge</strong>");
        this->ui->titleInfos->setStyleSheet("QLabel { color : red; }");

    }else if(color == Color::BLUE){
        this->ui->titleInfos->setText("Bleu");
        this->ui->titleInfos->setStyleSheet("QLabel { color : blue; }");
    }
}

void View::showWinner(){

    //The current player is losing
    Color winner = this->controller_->getGame().getCurrentPlayerColor();

    this->ui->infosLiveLabel->setText("<strong>Vous avez gagné !</strong>");

    if(winner == Color::BLUE){
        this->ui->titleInfos->setText("Joueur Rouge");
        this->ui->titleInfos->setStyleSheet("QLabel { color : red; }");
    }else{
        this->ui->titleInfos->setText("Joueur Bleu");
        this->ui->titleInfos->setStyleSheet("QLabel { color : blue; }");
    }
}

void View::showLastKilledPiece()
{
    std::vector<Piece> deadPieces = this->controller_->getGame().getDeadPiece();
    if(deadPieces.size() > 0){
        this->ui->labelKilledPiece->setVisible(true);
        for(unsigned i = 0; i < deadPieces.size(); i++){
            if(deadPieces.at(i).getColor() == Color::RED){
                this->ui->lastKilledRed->setVisible(true);

                this->ui->lastKilledRed->setText(QString::number(deadPieces.at(i).getLevel()));
                this->ui->lastKilledRed->setIcon(getIcon((deadPieces.at(i).getLevel())));
                this->ui->lastKilledRed->setStyleSheet("color: white;"
                                                       "background-color: red;");
                this->ui->lastKilledRed->setFixedSize(btnSize);
                this->ui->lastKilledRed->setIconSize(btnSize);
            }
            if(deadPieces.at(i).getColor() == Color::BLUE){
                this->ui->lastKilledBlue->setVisible(true);

                this->ui->lastKilledBlue->setText(QString::number(deadPieces.at(i).getLevel()));
                this->ui->lastKilledBlue->setIcon(getIcon((deadPieces.at(i).getLevel())));
                this->ui->lastKilledBlue->setStyleSheet("color: white;"
                                                        "background-color: blue;");
                this->ui->lastKilledBlue->setFixedSize(btnSize);
                this->ui->lastKilledBlue->setIconSize(btnSize);

            }
        }
    }
}

QIcon View::getIcon(int level)
{
    switch(level){
    case 0 :
        return QIcon("../Stratego_FinalV/resources/drapeau.jpg");
        break;
    case 1 :
        return QIcon("../Stratego_FinalV/resources/espion.jpg");
        break;
    case 2 :
        return QIcon("../Stratego_FinalV/resources/eclaireur.jpg");
        break;
    case 3 :
        return QIcon("../Stratego_FinalV/resources/demineur.jpg");
        break;
    case 4 :
        return QIcon("../Stratego_FinalV/resources/sergent.jpg");
        break;
    case 5 :
        return QIcon("../Stratego_FinalV/resources/lieutenant.jpg");
        break;
    case 6 :
        return QIcon("../Stratego_FinalV/resources/commandant.jpg");
        break;
    case 7 :
        return QIcon("../Stratego_FinalV/resources/capitaine.jpg");
        break;
    case 8 :
        return QIcon("../Stratego_FinalV/resources/colonel.jpg");
        break;
    case 9 :
        return QIcon("../Stratego_FinalV/resources/general.jpg");
        break;
    case 10 :
        return QIcon("../Stratego_FinalV/resources/marechal.jpg");
        break;
    case 11 :
        return QIcon("../Stratego_FinalV/resources/bombe.jpg");
        break;
    default : return QIcon();
    }
}

void View::showSelectedPieceInformations(){
    stratego::Position pos = this->controller_->getGame().getSelected();
    int level = this->controller_->getGame().getBoard().getPiece(pos)->getLevel();
    QString name = getName(level);
    name+= "<br> sélectionner <br> la case de destination";
    this->ui->infosLiveLabel->setText(name);
}

QString View::getName(int level)
{
    switch(level){
    case 0 :
        return QString("Drapeau");
        break;
    case 1 :
        return QString("Espionne");
        break;
    case 2 :
        return QString("Eclaireur");
        break;
    case 3 :
        return QString("Démineur");
        break;
    case 4 :
        return QString("Sergent");
        break;
    case 5 :
        return QString("Lieutenant");
        break;
    case 6 :
        return QString("Commandant");
        break;
    case 7 :
        return QString("Major");
        break;
    case 8 :
        return QString("Colonel");
        break;
    case 9 :
        return QString("Général");
        break;
    case 10 :
        return QString("Maréchal");
        break;
    case 11 :
        return QString("Bombe");
        break;
    default : return QString("Level non conforme");
    }
}


void View::addIconsBtns(QPushButton* button,const Position& pos,int level,QGridLayout * grid){
    switch(level){
    case 0 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/drapeau.jpg"));
        break;
    case 1 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/espion.jpg"));
        break;
    case 2 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/eclaireur.jpg"));
        break;
    case 3 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/demineur.jpg"));
        break;
    case 4 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/sergent.jpg"));
        break;
    case 5 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/lieutenant.jpg"));
        break;
    case 6 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/commandant.jpg"));
        break;
    case 7 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/capitaine.jpg"));
        break;
    case 8 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/colonel.jpg"));
        break;
    case 9 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/general.jpg"));
        break;
    case 10 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/marechal.jpg"));
        break;
    case 11 :
        button->setIcon(QIcon("../Stratego_FinalV/resources/bombe.jpg"));
        break;
    }
    button->setFixedSize(btnSize);
    button->setIconSize(btnSize);
    grid->addWidget(button,pos.x(),pos.y());

}



void View::on_menuChoice_activated(int index){
    if(index==0){
        this->difficulty = 0;
    }else{
        this->difficulty = 1;
    }
}

void View::clearInteractivesBoards()
{
    while ( QLayoutItem* item = ui->interactiv_select->layout()->takeAt( 0 ) )
    {
        Q_ASSERT( ! item->layout() );
        delete item->widget();
        delete item;
    }

    while ( QLayoutItem* item = ui->interactiv_put->layout()->takeAt( 0 ) )
    {
        Q_ASSERT( ! item->layout() );
        delete item->widget();
        delete item;
    }
}

void View::on_interactive_start_clicked(){


    //Initialization of the interactiv mod
    this->controller_->getGame().quitGame();
   this-> ui->stackedWidget->setCurrentIndex(2);
    this->setFixedSize(800,500);

    //Configuration of the all the elements.
    clearInteractivesBoards();
    this->controller_->getGame().interactivePlacement();
    this->secondPlayerTurn_ = false;
    this->nbPuttingOfPiece_ = 0;

    showInteractivSelectBoard(0,Color::BLUE);
    this->showInteractivPuttingBoard();
}

void View::showInteractivPuttingBoard(){
    ui->interactiv_put->setSpacing(0);
    for (int row {0} ; row < 4 ; row++ ) {
        for(int column{0}; column < 10 ; column++){
            stratego::Position pos(row,column);
            QPushButton * button = new QPushButton();
            button->setFixedSize(btnSize);
            this->ui->interactiv_put->addWidget(button,pos.x(),pos.y());

            connect(button,  &QPushButton::clicked,this, [=]() {
                if(!saveIcon_.isNull()){
                    if(button->icon().isNull()){
                        // Set the level of the button
                        QString levelString = "";
                        int level = this->saveLevel_;
                        levelString = QString::number(level);
                        button->setText(levelString);

                        // Set the icon of the button
                        button->setIcon(saveIcon_);
                        button->setIconSize(btnSize);
                        //used to put selectedIcon at null
                        saveIcon_ = tmp;

                        //Add the selected piece in the board
                        stratego::Position positionGameBordForSecondPlayer(pos.x()+6,pos.y());
                        if(this->saveNbStep_ == -1){
                            Piece p {this->saveLevel_,this->saveColor_};


                            // When it's the bottom player's turn (RED to lay the pieces down, then they start 6 rows down on the Stratego board
                            if(secondPlayerTurn_){
                                this->controller_->getGame().addPiece(positionGameBordForSecondPlayer,p);
                            }else{
                                this->controller_->getGame().addPiece(pos,p);
                            }
                        }else{
                            Piece p {this->saveLevel_,this->saveColor_,this->saveNbStep_};
                            if(secondPlayerTurn_){
                                this->controller_->getGame().addPiece(positionGameBordForSecondPlayer,p);
                            }else{
                                this->controller_->getGame().addPiece(pos,p);
                            }
                        }

                        //Set the color of the button
                        if(this->saveColor_ == Color::RED){
                            button->setStyleSheet("color: white;"
                                                  "background-color: red;");
                        }else{
                            button->setStyleSheet("color: white;"
                                                  "background-color: blue;");
                        }


                        this->nbPuttingOfPiece_ ++;
                        this->isPutted_ = true;


                        if(this->nbPuttingOfPiece_ == 40){
                            clearInteractivesBoards();
                            showInteractivSelectBoard(6,Color::RED);
                            showInteractivPuttingBoard();
                            secondPlayerTurn_ = true;
                        }

                        if(this->nbPuttingOfPiece_ == 80){
                            ui->stackedWidget->setCurrentIndex(1);
                            this->controller_->startInteractiveGame(difficulty);
                        }
                    }
                }
            }
            );
        }
    }
}

void View::showInteractivSelectBoard(int rowStart, const Color& color){
    int countVector = 0;

    for(int row = 0; row < 10 ;row++){
        for(int column = 0; column < 4; column++ ){
            stratego::Position pos(row,column);
            stratego::Position posGameBord(rowStart);
            QPushButton* button = new QPushButton();
            // Set the level on the button
            QString levelString = "";
            int level = this->controller_->getGame().getInteractiveRed().at(countVector).getLevel();
            levelString = QString::number(level);
            button->setText(levelString);


            // Set the color of the button
            if(color == Color::RED){
                button->setStyleSheet("color: white;"
                                      "background-color: red;");
            }else{
                button->setStyleSheet("color: white;"
                                      "background-color: blue;");
            }

            // Add the button with the correspondant icon
            addIconsBtns(button,pos,level,this->ui->interactiv_select);

            // interactiv_select
            connect(button,  &QPushButton::clicked,this, [=]() {


                if(isPutted_){
                    button->setEnabled(false);
                    this->saveIcon_ = button->icon();
                    this->saveLevel_ = level;
                    if(color == Color::RED){
                        this->saveNbStep_ = this->controller_->getGame().getInteractiveRed().at(countVector).getStep();
                        this->saveColor_ = controller_->getGame().getInteractiveRed().at(countVector).getColor();
                    }else{
                        this->saveNbStep_ =  this->controller_->getGame().getInteractiveBlue().at(countVector).getStep();
                        this->saveColor_ = controller_->getGame().getInteractiveBlue().at(countVector).getColor();
                    }

                    this->isPutted_=false;
                    button->setStyleSheet("color: black;"
                                          "background-color: black;");

                    button->setIcon(QIcon());
                }
            }
            );
            countVector++;
        }
    }
}

void View::on_file_start_clicked(){
    bool isFile = false;
    while(!isFile){
        QString filter = "Fichier Texte (*.txt) ";
        QString file_name =  QFileDialog::getOpenFileName(this,"Ouvrez le fichier des pions bleus","../Stratego_FinalV/config",filter);
        QFile file(file_name) ;

        if(!file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(this,"Erreur","Fichier non ouvert !");
        }else{
            QTextStream in (&file);
            this->pathBlue= file_name.toStdString();
            isFile = true;
        }
        file.close();

        QString filterRed = "Fichier Texte (*.txt) ";
        QString file_nameRed =  QFileDialog::getOpenFileName(this,"Ouvrez le fichier des pions rouges ","../Stratego_FinalV/config",filterRed);
        QFile fileRed(file_nameRed) ;
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(this,"Erreur","Fichier non ouvert !");
        }else{
            QTextStream in (&file);
            this->pathRed = file_name.toStdString();
            isFile = true;
        }
        fileRed.close();

    }
    controller_->startFileGame(difficulty,this->pathBlue,this->pathRed);
    ui->stackedWidget->setCurrentIndex(1);
}


void View::on_actionNouvelle_Partie_triggered(){
    this->controller_->getGame().quitGame();
    this->setFixedSize(500,500);
    ui->stackedWidget->setCurrentIndex(0);
}


void View::on_actionManuel_triggered(){
    QMessageBox msgBox;
    QString manuel("Stratego est jeu de stratégie jouable en 2 modes. \n"
    "\n"
    "1. Mode Interactif\n"
    "Le joueur bleu puis rouge va devoir remplir son plateau en sélectionnant une pièce parmi la liste des pièces disponibles,\n"
                   " le joueur devra ensuite sélectionner la case sur laquelle il souhaite placer cette pièce.\n"
    "\n"
    "2. Mode lecture de fichier\n"
    "Le bleu et rouge devront chacun fournir 1 fichier.txt contenant le niveau de chacun de leurs pièces (conformément au manuel du jeu officiel)\n"
    "\n"
    "3. IN GAME\n"
    "Pour jouer c'est très simple, à chaque tour le joueur courant\n"
    "- sélectionne une pièce déplaçable et lui appartenant.\n"
    "- sélectionne une case de destination possible.\n"
    "Sans quoi, le joueur courant va sera contraint de sélectionner à nouveau une pièce\n");
    msgBox.setText(manuel);
    msgBox.exec();
}


}
