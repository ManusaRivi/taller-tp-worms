#ifndef _COMANDO_SERVER
#define _COMANDO_SERVER

#include <iostream>
#include "../juego/mapa.h"


enum ESTADO{
    WALKING = 1,
    SALTANDO = 3,
    CAYENDO = 4, 
    HOLDING_BAZOOKA = 5,
    HOLDING_DINAMITA = 9,
    HOLDING_SANTA = 12,
    HOLDING_VERDE = 14,
    HOLDING_BANANA = 16,
    HOLDING_ROJA = 18
};



class Comando{

    uint32_t responsable_id;
    uint32_t tipo_comando;

    public:
    Comando();

    Comando(uint32_t id);


    virtual void realizar_accion(Mapa* mapa) = 0;

    uint32_t get_responsable();

    uint32_t get_comando();


};

#endif