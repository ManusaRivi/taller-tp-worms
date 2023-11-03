#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>
#include <string>

#include "mainwindow.h"

class Login {
    private:
    QApplication app;
    MainWindow mainWindow;
    
    public:
    Login(int, char**);
    ~Login();
    int start();
    //std::string getServer() const;
    //std::string getPort() const;
};

#endif
