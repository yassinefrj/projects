#ifndef MENU_H
#define MENU_H
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
namespace stratego{

class Menu : public QWidget{

    Q_OBJECT

    QComboBox *difficulty = new QComboBox;
    QVBoxLayout* VBox;
    QLabel* gameTitle;
public:
    Menu();
    void showMenu();

};

}
#endif // MENU_H
