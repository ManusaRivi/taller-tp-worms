#ifndef POCSDL_H
#define POCSDL_H

#include <iostream>
#include <exception>
#include <algorithm>
#include <string>
#include "protocolo/protocoloCliente.h"
#include "threads/containerThreads.h"
#include "comandos/comando.h"
#include "comandos/factory_comandos.h"

#include <SDL2pp/SDL2pp.hh>

class SDLPoc {
    public:
    SDLPoc();
    int run();
};

#endif