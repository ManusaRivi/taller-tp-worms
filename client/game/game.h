#ifndef GAME_H
#define GAME_H

#define FRAME_RATE 33

#include <SDL2pp/SDL2pp.hh>
#include "Texturas/texture_manager.h"
#include "../protocolo/protocoloCliente.h"
#include <vector>
#include <unistd.h>
#include "../../common/queue.h"
#include "comunicacion/snapshot.h"
#include "../comandos/comando.h"
#include "../comandos/factory_comandos.h"
#include "../comandos/mensaje.h"

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