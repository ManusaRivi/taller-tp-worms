#include "factory_comandos.h"

FactoryComandos::FactoryComandos(){

}

std::shared_ptr<ComandoMover> FactoryComandos::accion_mover(uint8_t dir){
    return std::make_shared<ComandoMover>(dir);
}

std::shared_ptr<DetenerMovimiento> FactoryComandos::accion_detener(){
    return std::make_shared<DetenerMovimiento>();
}