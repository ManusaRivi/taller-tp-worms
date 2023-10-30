#ifndef _COMANDO
#define _COMANDO

#include <iostream>

struct Comando{

    uint8_t tipo_comando;
    uint8_t responsable_id;
    uint8_t dir;

    public:
    Comando(uint8_t dir,uint8_t tipo);
    Comando(){};

    uint8_t get_tipo();

    void agregar_id(uint8_t id);

    uint8_t get_direccion();

};

#endif