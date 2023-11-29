#ifndef _FACTORY
#define _FACTORY
#include "comando_mover.h"
#include "comando_detener_movimiento.h"
#include "comando_disparar.h"
#include "comando_cambiar_arma.h"
#include "comando_cargar_arma.h"
#include "comando_saltar.h"
#include "comando_detener_angulo.h"
#include "comando_cambiar_angulo.h"
#include "comando_cambiar_direccion_arma.h"
#include "comando_setear_timer.h"
#include "comando_setear_target.h"

class FactoryComandos{

    public:
    FactoryComandos();

    std::shared_ptr<ComandoMoverCliente> accion_mover(uint8_t dir);

    std::shared_ptr<DetenerMovimientoCliente> accion_detener();

    std::shared_ptr<DispararArmaCliente> accion_disparar();

    std::shared_ptr<SaltarCliente> accion_saltar(uint8_t direccion);

    std::shared_ptr<CambiarArmaCliente> accion_cambiar_arma(uint8_t tipo_arma);

    std::shared_ptr<CargarArmaCliente> accion_cargar_arma();

    std::shared_ptr<DetenerAnguloCliente> accion_detener_cambio_angulo();

    std::shared_ptr<CambiarAnguloCliente> accion_cambiar_angulo(uint8_t dir);

    std::shared_ptr<CambiarDireccionArmaCliente> accion_cambiar_direccion_arma(uint8_t dir);

    std::shared_ptr<SetearTimerCliente> accion_setear_timer(uint32_t time);

    std::shared_ptr<SetearTargetCliente> accion_setear_target(float x, float y);




};

#endif