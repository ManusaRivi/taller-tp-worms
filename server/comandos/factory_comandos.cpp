#include "factory_comandos.h"

FactoryComandos::FactoryComandos(){

}

std::shared_ptr<ComandoMovimiento> FactoryComandos::comando_movimiento(uint8_t dir, uint8_t id){
        return std::make_shared<ComandoMovimiento>(dir,id);
}