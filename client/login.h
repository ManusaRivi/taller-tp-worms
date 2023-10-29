#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>

#include "mainwindow.h"

class Login {
    private:
    QApplication app;
    MainWindow mainWindow;
    
    public:
    Login(int, char**);
    ~Login();
    int start();
};

#endif
