#include "factory_mensajes.h"


FactoryMensaje::FactoryMensaje(){}


std::shared_ptr<MensajeAccionJugador> FactoryMensaje::cambiar_angulo(uint8_t direccion){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_cambiar_angulo(direccion);
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;

}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::cambiar_arma(uint8_t id_arma){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_cambiar_arma(id_arma);
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::cargar_arma(){
std::shared_ptr<ComandoCliente> cmd = factory.accion_cargar_arma();
    shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::saltar(uint8_t direccion){
std::shared_ptr<ComandoCliente> cmd = factory.accion_saltar(direccion);
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::disparar(){
std::shared_ptr<ComandoCliente> cmd = factory.accion_disparar();
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::moverse(uint8_t direccion){
std::shared_ptr<ComandoCliente> cmd = factory.accion_mover(direccion);
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::detener_angulo(){
std::shared_ptr<ComandoCliente> cmd = factory.accion_detener_cambio_angulo();
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::detener_movimiento(){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_detener();
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::cambiar_direccion_arma(uint8_t direccion){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_cambiar_direccion_arma(direccion);
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::setear_timer(uint32_t time){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_setear_timer(time);
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::setear_target(float x, float y){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_setear_target(x,y);
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}

std::shared_ptr<MensajeAccionJugador> FactoryMensaje::activar_cheat(uint8_t tipo_de_cheat){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_cheat(tipo_de_cheat);
    std::shared_ptr<MensajeAccionJugador> msg = make_shared<MensajeAccionJugador>(cmd);
    return msg;
}




