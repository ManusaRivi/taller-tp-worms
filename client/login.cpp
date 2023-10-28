#include <QApplication>

#include "mainwindow.h"
#include "login.h"

Login::Login(int argc, char** argv) : app(argc, argv) {}

Login::~Login() {}

int Login::start() {
    MainWindow menu;
    menu.show();
    return this->app.exec();
}
