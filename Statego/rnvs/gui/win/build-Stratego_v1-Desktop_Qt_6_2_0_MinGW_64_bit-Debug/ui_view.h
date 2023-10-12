/********************************************************************************
** Form generated from reading UI file 'view.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_View
{
public:
    QAction *actionQuitter;
    QAction *actionNouvelle_Partie;
    QAction *actionManuel;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *start_Menu;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *menuBox;
    QLabel *difficulty;
    QComboBox *menuChoice;
    QLabel *fillingMod;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *interactive_start;
    QPushButton *file_start;
    QLabel *gameTitle;
    QWidget *game;
    QWidget *gridLayoutWidget;
    QGridLayout *game_G;
    QLabel *titleInfos;
    QLabel *infosLiveLabel;
    QPushButton *lastKilledRed;
    QPushButton *lastKilledBlue;
    QLabel *labelKilledPiece;
    QLabel *label_2;
    QWidget *interactive_P;
    QWidget *gridLayoutWidget_2;
    QGridLayout *interactiv_put;
    QWidget *gridLayoutWidget_3;
    QGridLayout *interactiv_select;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QMenu *menuJeu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *View)
    {
        if (View->objectName().isEmpty())
            View->setObjectName(QString::fromUtf8("View"));
        View->setWindowModality(Qt::ApplicationModal);
        View->resize(828, 521);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(View->sizePolicy().hasHeightForWidth());
        View->setSizePolicy(sizePolicy);
        View->setMinimumSize(QSize(500, 500));
        View->setMaximumSize(QSize(1500, 16777215));
        QFont font;
        font.setPointSize(14);
        View->setFont(font);
        View->setWindowOpacity(1.000000000000000);
        actionQuitter = new QAction(View);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionNouvelle_Partie = new QAction(View);
        actionNouvelle_Partie->setObjectName(QString::fromUtf8("actionNouvelle_Partie"));
        actionManuel = new QAction(View);
        actionManuel->setObjectName(QString::fromUtf8("actionManuel"));
        centralwidget = new QWidget(View);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(1000, 1000));
        centralwidget->setMaximumSize(QSize(1600, 1050));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 831, 501));
        start_Menu = new QWidget();
        start_Menu->setObjectName(QString::fromUtf8("start_Menu"));
        verticalLayoutWidget = new QWidget(start_Menu);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 50, 481, 411));
        menuBox = new QVBoxLayout(verticalLayoutWidget);
        menuBox->setSpacing(40);
        menuBox->setObjectName(QString::fromUtf8("menuBox"));
        menuBox->setSizeConstraint(QLayout::SetNoConstraint);
        menuBox->setContentsMargins(0, 20, 0, 70);
        difficulty = new QLabel(verticalLayoutWidget);
        difficulty->setObjectName(QString::fromUtf8("difficulty"));
        difficulty->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(difficulty->sizePolicy().hasHeightForWidth());
        difficulty->setSizePolicy(sizePolicy1);
        difficulty->setMinimumSize(QSize(450, 20));
        difficulty->setMaximumSize(QSize(450, 20));
        QFont font1;
        font1.setPointSize(11);
        difficulty->setFont(font1);
        difficulty->setTextFormat(Qt::PlainText);
        difficulty->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        menuBox->addWidget(difficulty);

        menuChoice = new QComboBox(verticalLayoutWidget);
        menuChoice->addItem(QString());
        menuChoice->addItem(QString());
        menuChoice->setObjectName(QString::fromUtf8("menuChoice"));
        menuChoice->setFont(font1);

        menuBox->addWidget(menuChoice, 0, Qt::AlignHCenter);

        fillingMod = new QLabel(verticalLayoutWidget);
        fillingMod->setObjectName(QString::fromUtf8("fillingMod"));
        sizePolicy.setHeightForWidth(fillingMod->sizePolicy().hasHeightForWidth());
        fillingMod->setSizePolicy(sizePolicy);
        fillingMod->setFont(font1);

        menuBox->addWidget(fillingMod, 0, Qt::AlignHCenter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 50, -1, -1);
        interactive_start = new QPushButton(verticalLayoutWidget);
        interactive_start->setObjectName(QString::fromUtf8("interactive_start"));
        interactive_start->setFont(font1);

        horizontalLayout_2->addWidget(interactive_start);

        file_start = new QPushButton(verticalLayoutWidget);
        file_start->setObjectName(QString::fromUtf8("file_start"));
        file_start->setFont(font1);

        horizontalLayout_2->addWidget(file_start);


        menuBox->addLayout(horizontalLayout_2);

        gameTitle = new QLabel(start_Menu);
        gameTitle->setObjectName(QString::fromUtf8("gameTitle"));
        gameTitle->setGeometry(QRect(170, 0, 151, 41));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gameTitle->sizePolicy().hasHeightForWidth());
        gameTitle->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setPointSize(22);
        gameTitle->setFont(font2);
        gameTitle->setStyleSheet(QString::fromUtf8("h1 {\n"
"	font: 900 9pt \"Arial Black\";\n"
"	font: 24pt \"Segoe UI\";\n"
"  text-align: center;\n"
"  color: white;\n"
"  text-transform: uppercase;\n"
"  padding: 1px;\n"
"  font-family: \"Raleway\", cursive;\n"
"  font-weight: 100;\n"
"  position: relative;\n"
"  width: 100%;\n"
"  background: linear-gradient(to right, black, #eee, black);\n"
"  white-space: nowrap;\n"
"}\n"
"h1::before {\n"
"  content: \"\";\n"
"  position: absolute;\n"
"  left: 50%;\n"
"  top: -50px;\n"
"  width: 600px;\n"
"  margin-left: -300px;\n"
"  margin-top: -220px;\n"
"  height: 600px;\n"
"  background: radial-gradient(ellipse closest-side, #444, black);\n"
"  z-index: -1;\n"
"}\n"
"h1 a {\n"
"  background: black;\n"
"  display: block;\n"
"  padding: 20px;\n"
"  text-decoration: none;\n"
"  letter-spacing: 30px;\n"
"  color: white;\n"
"}\n"
"\n"
"body {\n"
"  background: black;\n"
"  display: grid;\n"
"  place-items: center;\n"
"  height: 100vh;\n"
"  margin: 0;\n"
"  overflow: hidden;\n"
"}"));
        gameTitle->setFrameShape(QFrame::WinPanel);
        stackedWidget->addWidget(start_Menu);
        game = new QWidget();
        game->setObjectName(QString::fromUtf8("game"));
        gridLayoutWidget = new QWidget(game);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 20, 441, 431));
        game_G = new QGridLayout(gridLayoutWidget);
        game_G->setObjectName(QString::fromUtf8("game_G"));
        game_G->setSizeConstraint(QLayout::SetDefaultConstraint);
        game_G->setHorizontalSpacing(6);
        game_G->setVerticalSpacing(10);
        game_G->setContentsMargins(0, 0, 0, 0);
        titleInfos = new QLabel(game);
        titleInfos->setObjectName(QString::fromUtf8("titleInfos"));
        titleInfos->setGeometry(QRect(470, 30, 311, 91));
        QFont font3;
        font3.setPointSize(28);
        font3.setBold(false);
        titleInfos->setFont(font3);
        titleInfos->setAlignment(Qt::AlignCenter);
        infosLiveLabel = new QLabel(game);
        infosLiveLabel->setObjectName(QString::fromUtf8("infosLiveLabel"));
        infosLiveLabel->setGeometry(QRect(470, 140, 301, 181));
        QFont font4;
        font4.setPointSize(20);
        infosLiveLabel->setFont(font4);
        infosLiveLabel->setAlignment(Qt::AlignCenter);
        lastKilledRed = new QPushButton(game);
        lastKilledRed->setObjectName(QString::fromUtf8("lastKilledRed"));
        lastKilledRed->setGeometry(QRect(510, 400, 91, 61));
        lastKilledBlue = new QPushButton(game);
        lastKilledBlue->setObjectName(QString::fromUtf8("lastKilledBlue"));
        lastKilledBlue->setGeometry(QRect(660, 400, 93, 61));
        labelKilledPiece = new QLabel(game);
        labelKilledPiece->setObjectName(QString::fromUtf8("labelKilledPiece"));
        labelKilledPiece->setGeometry(QRect(470, 330, 301, 51));
        QFont font5;
        font5.setPointSize(15);
        font5.setKerning(true);
        labelKilledPiece->setFont(font5);
        labelKilledPiece->setLayoutDirection(Qt::LeftToRight);
        labelKilledPiece->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(game);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 20, 431, 421));
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(../Stratego_FinalV/resources/war.png)"));
        stackedWidget->addWidget(game);
        label_2->raise();
        gridLayoutWidget->raise();
        titleInfos->raise();
        infosLiveLabel->raise();
        lastKilledRed->raise();
        lastKilledBlue->raise();
        labelKilledPiece->raise();
        interactive_P = new QWidget();
        interactive_P->setObjectName(QString::fromUtf8("interactive_P"));
        gridLayoutWidget_2 = new QWidget(interactive_P);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(20, 60, 431, 361));
        interactiv_put = new QGridLayout(gridLayoutWidget_2);
        interactiv_put->setObjectName(QString::fromUtf8("interactiv_put"));
        interactiv_put->setSizeConstraint(QLayout::SetDefaultConstraint);
        interactiv_put->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_3 = new QWidget(interactive_P);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(480, 10, 321, 451));
        interactiv_select = new QGridLayout(gridLayoutWidget_3);
        interactiv_select->setObjectName(QString::fromUtf8("interactiv_select"));
        interactiv_select->setContentsMargins(0, 0, 0, 0);
        stackedWidget->addWidget(interactive_P);
        View->setCentralWidget(centralwidget);
        menubar = new QMenuBar(View);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 828, 33));
        QFont font6;
        font6.setPointSize(12);
        menubar->setFont(font6);
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuHelp->setFont(font1);
        menuJeu = new QMenu(menubar);
        menuJeu->setObjectName(QString::fromUtf8("menuJeu"));
        View->setMenuBar(menubar);
        statusbar = new QStatusBar(View);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setFont(font6);
        View->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menubar->addAction(menuJeu->menuAction());
        menuHelp->addAction(actionManuel);
        menuJeu->addAction(actionNouvelle_Partie);

        retranslateUi(View);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(View);
    } // setupUi

    void retranslateUi(QMainWindow *View)
    {
        View->setWindowTitle(QCoreApplication::translate("View", "Stratego", nullptr));
        actionQuitter->setText(QCoreApplication::translate("View", "Quitter", nullptr));
        actionNouvelle_Partie->setText(QCoreApplication::translate("View", "Nouvelle Partie", nullptr));
        actionManuel->setText(QCoreApplication::translate("View", "Manuel", nullptr));
        difficulty->setText(QCoreApplication::translate("View", "Choisissez la difficult\303\251e souhait\303\251e :", nullptr));
        menuChoice->setItemText(0, QCoreApplication::translate("View", "Amateur", nullptr));
        menuChoice->setItemText(1, QCoreApplication::translate("View", "Normal", nullptr));

        fillingMod->setText(QCoreApplication::translate("View", "Quel mode de remplissage des pions souhaitez-vous ? ", nullptr));
        interactive_start->setText(QCoreApplication::translate("View", "Mode Interactif", nullptr));
        file_start->setText(QCoreApplication::translate("View", "Chargement Fichiers", nullptr));
        gameTitle->setText(QCoreApplication::translate("View", "STRATEGO", nullptr));
        titleInfos->setText(QCoreApplication::translate("View", "Couleur", nullptr));
        infosLiveLabel->setText(QCoreApplication::translate("View", "Infos en live", nullptr));
        lastKilledRed->setText(QString());
        lastKilledBlue->setText(QString());
        labelKilledPiece->setText(QCoreApplication::translate("View", "Derni\303\250re pi\303\250ce captur\303\251e", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("View", "Aide", nullptr));
        menuJeu->setTitle(QCoreApplication::translate("View", "Jeu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class View: public Ui_View {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_H
