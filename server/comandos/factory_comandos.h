#ifndef _FACTORY
#define _FACTORY
#include <iostream>
#include <memory>
#include "comando.h"
#include "comando_movimiento.h"


struct FactoryComandos{

    FactoryComandos();

    std::shared_ptr<ComandoMovimiento> comando_movimiento(uint8_t dir, uint8_t id);

};

#endif