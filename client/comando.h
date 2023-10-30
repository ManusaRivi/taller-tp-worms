#ifndef _COMANDO
#define _COMANDO
#include <iostream>

struct Comando{

    uint8_t tipo_comando;
    uint8_t dir;

    Comando();

    void agregar_tipo(uint8_t tipo);

    void agregar_direccion(uint8_t dir);

};


#endif