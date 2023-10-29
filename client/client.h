#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>


#include "login.h"
#include "game.h"
#include "protocolo/protocoloCliente.h"

class Client {
    private:
    Login login;
    //Protocolo protocol;

    public:
    Client(int, char**);

    int iniciar();
};

#endif