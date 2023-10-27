#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QMainWindow {
    Q_OBJECT

    private:
    Ui::Menu *ui;

    public:
    Menu(QWidget* parent = nullptr);
    ~Menu();
};

#endif
