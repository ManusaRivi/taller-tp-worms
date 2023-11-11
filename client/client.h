#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>


#include "login.h"
#include "game/game.h"
#include "protocolo/protocoloCliente.h"
#include "threads/containerThreads.h"
#include "../common/socket.h"

class Client {


    private:
    Socket* skt;
    Login login;
    
    public:
    Client(int, char**);
    ~Client();

    int iniciar();

    void crear_partida();

    void imprimir_partidas_disponibles(std::map<uint32_t,std::string> partidas);
};

#endif