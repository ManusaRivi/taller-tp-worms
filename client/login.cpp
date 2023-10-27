#include <QApplication>

#include "menu.h"
#include "login.h"

Login::Login(int argc, char** argv) : app(argc, argv) {}

Login::~Login() {}

int Login::start() {
    Menu menu;
    menu.show();
    return this->app.exec();
}
