#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>


#include "login.h"
#include "game/game.h"
#include "protocolo/protocoloCliente.h"
#include "threads/containerThreads.h"

class Client {


    private:
    Login login;
    //Protocolo protocol;

    public:
    Client(int, char**);

    int iniciar();

    void crear_partida(Socket &skt);

    void imprimir_partidas_disponibles(std::map<uint32_t,std::string> partidas);
};

#endif