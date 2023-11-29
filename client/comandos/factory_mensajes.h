#ifndef _FactoryMensajeCliente
#define _FactoryMensajeCliente

#include "factory_comandos.h"
#include "mensajes/mensaje_accion_jugador.h"

using namespace std;

class FactoryMensaje{

    private:
    FactoryComandos factory;

    public:
    FactoryMensaje();

    std::shared_ptr<MensajeAccionJugador> moverse(uint8_t dir);
    std::shared_ptr<MensajeAccionJugador> disparar();
    std::shared_ptr<MensajeAccionJugador> saltar(uint8_t dir);
    std::shared_ptr<MensajeAccionJugador> cargar_arma();
    std::shared_ptr<MensajeAccionJugador> cambiar_arma(uint8_t id_arma);
    std::shared_ptr<MensajeAccionJugador> cambiar_angulo(uint8_t direccion);
    std::shared_ptr<MensajeAccionJugador> detener_movimiento();
    std::shared_ptr<MensajeAccionJugador> detener_angulo();
    std::shared_ptr<MensajeAccionJugador> cambiar_direccion_arma(uint8_t dir);
    std::shared_ptr<MensajeAccionJugador> setear_timer(uint32_t time);
    std::shared_ptr<MensajeAccionJugador> setear_target(float x, float y);


};




#endif