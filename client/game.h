#ifndef GAME_H
#define GAME_H

#include <SDL2pp/SDL2pp.hh>
#include "protocolo/protocoloCliente.h"
#include <vector>
#include "../../common/queue.h"
#include "snapshot.h"
#include "comandos/comando.h"
#include "comandos/factory_comandos.h"
#include "comandos/mensaje.h"

class Game {
    private:
    Queue<Mensaje> &snapshots;
    Queue<Mensaje> &acciones;
    FactoryComandos factory;

    public:
    Game(Queue<Mensaje> &snapshots, Queue<Mensaje> &acciones);

    int run();

};

#endif