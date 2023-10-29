#include <QApplication>
#include <string>

#include "mainwindow.h"
#include "login.h"

Login::Login(int argc, char** argv) : app(argc, argv), mainWindow() {}

Login::~Login() {}

int Login::start() {
    this->mainWindow.show();
    return this->app.exec();
}

std::string Login::getServer() const {
    return this->mainWindow.getServer();
}

std::string Login::getPort() const {
    return this->mainWindow.getPort();
}