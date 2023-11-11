#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>
#include <string>

#include "mainwindow.h"
#include "../../common/socket.h"

class Login {
    private:
    QApplication app;
    MainWindow mainWindow;
    
    public:
    Login(int, char**, Socket*);
    ~Login();
    int start();
    Socket* getSocket();
};

#endif
