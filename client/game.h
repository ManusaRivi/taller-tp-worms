#ifndef GAME_H
#define GAME_H

#include <SDL2pp/SDL2pp.hh>
#include "protocolo/protocoloCliente.h"
#include <vector>
#include "../../common/queue.h"
#include "snapshot.h"
#include "comando.h"

class Game {
    private:
    Queue<Snapshot> &snapshots;
    Queue<Comando> &acciones;

    public:
    Game(Queue<Snapshot> &snapshots, Queue<Comando> &acciones);

    int run();

};

#endif