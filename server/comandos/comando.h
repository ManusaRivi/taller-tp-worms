#ifndef _COMANDO
#define _COMANDO

#include <iostream>
#include "../juego/mapa.h"
struct Comando{

    uint8_t responsable_id;
    uint8_t dir;

    public:
    Comando();


    virtual void agregar_id(uint8_t id) = 0;

    virtual void realizar_accion(Mapa &mapa) = 0;


};

#endif