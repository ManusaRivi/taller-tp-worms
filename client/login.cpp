#include <QApplication>
#include <string>

#include "mainwindow.h"
#include "login.h"
#include "../common/socket.h"

Login::Login(int argc, char** argv, Socket* skt) : app(argc, argv), mainWindow(nullptr, skt) {}

Login::~Login() {}

int Login::start() {
    this->mainWindow.show();
    return this->app.exec();
}
