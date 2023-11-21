#include "factory_comandos.h"

using namespace std;

FactoryComandos::FactoryComandos(){

}

std::shared_ptr<ComandoMoverCliente> FactoryComandos::accion_mover(uint8_t dir){
    return std::make_shared<ComandoMoverCliente>(dir);
}

std::shared_ptr<DetenerMovimientoCliente> FactoryComandos::accion_detener(){
    return std::make_shared<DetenerMovimientoCliente>();
}

std::shared_ptr<SaltarCliente> FactoryComandos::accion_saltar(uint8_t direccion){
    return make_shared<SaltarCliente>(direccion);
}

std::shared_ptr<DispararArmaCliente> FactoryComandos::accion_disparar(){
    return make_shared<DispararArmaCliente>();
}

std::shared_ptr<DetenerAnguloCliente> FactoryComandos::accion_detener_cambio_angulo(){
    return make_shared<DetenerAnguloCliente>();
}

shared_ptr<CambiarArmaCliente> FactoryComandos::accion_cambiar_arma(uint8_t id_arma){
    return make_shared<CambiarArmaCliente>(id_arma);
}

shared_ptr<CambiarAnguloCliente> FactoryComandos::accion_cambiar_angulo(uint8_t dir){
    return make_shared<CambiarAnguloCliente>(dir);
}

shared_ptr<CargarArmaCliente> FactoryComandos::accion_cargar_arma(){
    return make_shared<CargarArmaCliente>();
}

shared_ptr<CambiarDireccionArmaCliente> FactoryComandos::accion_cambiar_direccion_arma(uint8_t dir){
    return make_shared<CambiarDireccionArmaCliente>(dir);
}