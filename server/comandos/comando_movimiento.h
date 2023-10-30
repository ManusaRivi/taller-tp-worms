#ifndef _COMANDOMOVIMIENTO
#define _COMANDOMOVIMIENTO
#include "comando.h"

struct ComandoMovimiento:public Comando{

    uint8_t dir;

    ComandoMovimiento(uint8_t direccion);

    uint8_t get_direccion();

};

#endif