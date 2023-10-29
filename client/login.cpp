#include <QApplication>

#include "mainwindow.h"
#include "login.h"

Login::Login(int argc, char** argv) : app(argc, argv), mainWindow() {}

Login::~Login() {}

int Login::start() {
    this->mainWindow.show();
    return this->app.exec();
}
