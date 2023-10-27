#include "menu.h"
#include "ui/ui_menu.h"

Menu::Menu(QWidget* parent) : QMainWindow(parent), ui(new Ui::Menu) {
    this->ui->setupUi(this);
}

Menu::~Menu() {
    delete this->ui;
}
