#ifndef _FACTORY
#define _FACTORY
#include "comando.h"
#include "comando_movimiento.h"

struct FactoryComandos{

    FactoryComandos();

    ComandoMovimiento comando_movimient(uint8_t dir);

};

#endif