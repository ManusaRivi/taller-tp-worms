#ifndef _FACTORY
#define _FACTORY
#include <iostream>
#include <memory>
#include "comando_movimiento.h"
#include "comando_detener_movimiento.h"
#include "comando_empezar_partida.h"


class EmpezarPartida;
class FactoryComandos{

    public:

    FactoryComandos();

    std::shared_ptr<ComandoMovimiento> comando_movimiento(uint8_t dir, uint8_t id);

    // std::shared_ptr<CrearPartida> comando_crear_partida(std::string nombre, uint8_t tipo);

    std::shared_ptr<DetenerMovimiento> comando_detener(); 

    std::shared_ptr<EmpezarPartida> comando_empezar();

    ~FactoryComandos();

};

#endif