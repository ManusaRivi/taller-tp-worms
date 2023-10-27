#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>

class Login {
    private:
    QApplication app;
    
    public:
    Login(int, char**);
    ~Login();
    int start();
};

#endif
