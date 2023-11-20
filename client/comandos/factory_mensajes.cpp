#include "factory_mensajes.h"


FactoryMensaje::FactoryMensaje(){}


std::shared_ptr<MensajeCliente> FactoryMensaje::cambiar_angulo(uint8_t direccion){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_cambiar_angulo(direccion);
    std::shared_ptr<MensajeCliente> msg = make_shared<MensajeCliente>(cmd);
    return msg;

}

std::shared_ptr<MensajeCliente> FactoryMensaje::cambiar_arma(uint8_t id_arma){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_cambiar_arma(id_arma);
    std::shared_ptr<MensajeCliente> msg = make_shared<MensajeCliente>(cmd);
    return msg;
}

std::shared_ptr<MensajeCliente> FactoryMensaje::cargar_arma(){
std::shared_ptr<ComandoCliente> cmd = factory.accion_cargar_arma();
    shared_ptr<MensajeCliente> msg = make_shared<MensajeCliente>(cmd);
    return msg;
}

std::shared_ptr<MensajeCliente> FactoryMensaje::saltar(uint8_t direccion){
std::shared_ptr<ComandoCliente> cmd = factory.accion_saltar(direccion);
    std::shared_ptr<MensajeCliente> msg = make_shared<MensajeCliente>(cmd);
    return msg;
}

std::shared_ptr<MensajeCliente> FactoryMensaje::disparar(){
std::shared_ptr<ComandoCliente> cmd = factory.accion_disparar();
    std::shared_ptr<MensajeCliente> msg = make_shared<MensajeCliente>(cmd);
    return msg;
}

std::shared_ptr<MensajeCliente> FactoryMensaje::moverse(uint8_t direccion){
std::shared_ptr<ComandoCliente> cmd = factory.accion_mover(direccion);
    std::shared_ptr<MensajeCliente> msg = make_shared<MensajeCliente>(cmd);
    return msg;
}

std::shared_ptr<MensajeCliente> FactoryMensaje::detener_angulo(){
std::shared_ptr<ComandoCliente> cmd = factory.accion_detener_cambio_angulo();
    std::shared_ptr<MensajeCliente> msg = make_shared<MensajeCliente>(cmd);
    return msg;
}

std::shared_ptr<MensajeCliente> FactoryMensaje::detener_movimiento(){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_detener();
    std::shared_ptr<MensajeCliente> msg = make_shared<MensajeCliente>(cmd);
    return msg;
}

std::shared_ptr<MensajeCliente> FactoryMensaje::cambiar_direccion_arma(uint8_t direccion){
    std::shared_ptr<ComandoCliente> cmd = factory.accion_cambiar_direccion_arma(direccion);
    std::shared_ptr<MensajeCliente> msg = make_shared<MensajeCliente>(cmd);
    return msg;
}
