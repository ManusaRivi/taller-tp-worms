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


const std::string Login::getServer() {
    return this->mainWindow.getServer();
}

const std::string Login::getPort() {
    return this->mainWindow.getPort();
}
