#ifndef _COMANDO_SERVER
#define _COMANDO_SERVER

#include <iostream>
#include "../juego/mapa.h"
class Comando{

    public:

    uint32_t responsable_id;
    uint8_t dir;
    uint8_t id_gusano;
    uint8_t tipo_comando;

    public:
    Comando();

    Comando(uint32_t id);


    virtual void agregar_id(uint8_t id) = 0;

    virtual void realizar_accion(Mapa &mapa, uint32_t id) = 0;

    virtual uint8_t get_comando() = 0;

    uint32_t get_responsable();


};

#endif