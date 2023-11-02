#ifndef _FACTORY
#define _FACTORY
#include "comando_mover.h"
#include "comando_detener_movimiento.h"

struct FactoryComandos{

    FactoryComandos();

    std::shared_ptr<ComandoMover> accion_mover(uint8_t dir);

    std::shared_ptr<DetenerMovimiento> accion_detener();

};

#endif