#ifndef _FACTORY
#define _FACTORY
#include <iostream>
#include <memory>
#include "movimiento.h"
#include "detener_movimiento.h"
#include "empezar_partida.h"
#include "cambiar_angulo.h"
#include "cambiar_arma.h"
#include "saltar.h"
#include "disparar.h"
#include "detener_angulo.h"
#include "cargar_arma.h"
#include "cambiar_direccion_arma.h"
#include "mensajes/mensaje.h"


class EmpezarPartida;
class FactoryComandos{

    public:

    FactoryComandos();

    std::shared_ptr<ComandoMovimiento> comando_movimiento(uint8_t dir, uint32_t id);

    // std::shared_ptr<CrearPartida> comando_crear_partida(std::string nombre, uint8_t tipo);

    std::shared_ptr<DetenerMovimiento> comando_detener(uint32_t id); 

    std::shared_ptr<EmpezarPartida> comando_empezar();

    std::shared_ptr<Disparar> comando_disparar(uint32_t id);
    std::shared_ptr<CargarArma> comando_cargar_arma(uint32_t id);
    std::shared_ptr<Saltar> comando_saltar(uint32_t id, uint8_t dir);
    std::shared_ptr<CambiarAngulo> comando_cambiar_angulo(uint32_t id, uint8_t direccion);
    std::shared_ptr<DetenerAngulo> comando_detener_angulo(uint32_t id);
    std::shared_ptr<CambiarArma> comando_cambiar_arma(uint32_t id, uint8_t tipo_arma);
    std::shared_ptr<CambiarDireccionArma> comando_cambia_direccion_arma(uint32_t id, uint8_t dir);
    

    ~FactoryComandos();

};

#endif