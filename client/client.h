#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>


#include "login.h"
#include "game.h"
#include "protocolo/protocoloCliente.h"

class Client {
    private:
    Login login;
    Socket skt;
    Protocolo protocol;
    

    public:
    Client(int, char**,const char*,const char*);

    int iniciar();
};

#endif