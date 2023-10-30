#ifndef POCSDL_H
#define POCSDL_H

#include <iostream>
#include <exception>
#include <algorithm>
#include <string>
#include "protocolo/protocoloCliente.h"
#include "threads/containerThreads.h"
#include "comando.h"

#include <SDL2pp/SDL2pp.hh>

class SDLPoc {
        Queue<Snapshot> &snapshots;
    Queue<Comando> &acciones;
    public:
    SDLPoc(Queue<Snapshot> &snapshots, Queue<Comando> &acciones);
    int run();
};

#endif