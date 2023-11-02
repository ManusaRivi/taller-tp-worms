#ifndef GAME_H
#define GAME_H

#include <SDL2pp/SDL2pp.hh>
#include "protocolo/protocoloCliente.h"
#include <vector>
#include "../../common/queue.h"
#include "snapshot.h"
#include "comandos/comando.h"
#include "comandos/factory_comandos.h"

class Game {
    private:
    Queue<Snapshot> &snapshots;
    Queue<std::shared_ptr<Comando>> &acciones;
    FactoryComandos factory;

    public:
    Game(Queue<Snapshot> &snapshots, Queue<std::shared_ptr<Comando>> &acciones);

    int run();

};

#endif