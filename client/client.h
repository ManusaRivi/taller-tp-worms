#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>


#include "login.h"
#include "game.h"
//#include "protocol.h"

class Client {
    private:
    Login login;
    //Menu menu;
    //Protocol protocol;

    public:
    Client(int, char**);

    int iniciar();
};

#endif