#ifndef POCSDL_H
#define POCSDL_H

#include <iostream>
#include <exception>
#include <algorithm>
#include <string>
#include "protocolo/protocoloCliente.h"

#include <SDL2pp/SDL2pp.hh>

class SDLPoc {
    Protocolo& protocolo;
    public:
    SDLPoc(Protocolo&);
    int run();
};

#endif