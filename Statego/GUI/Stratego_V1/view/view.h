#ifndef VIEW_H
#define VIEW_H
#include "qpushbutton.h"
#include "utils/observer.h"
#include <QMainWindow>
#include <QWidget>

namespace Ui
{
class View;
}

namespace stratego
{
class Controller;
}


namespace stratego{

class View : public QMainWindow , public nvs::Observer{

    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);
    Controller* controller_ = nullptr;
    void setCtrl( Controller * ctrl);
    ~View();
    void showBoard();
    void clearBoard();

private slots:


    void on_comboBox_4_activated(int index);

    void on_blueBtn_4_clicked();

    void on_redBtn_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::View * ui;
    int difficulty ; //0 is beginner ,...
    std::string pathBlue;
    std::string pathRed;
    void update(const nvs::Subject *subject) override;
};

}
#endif // VIEW_H
