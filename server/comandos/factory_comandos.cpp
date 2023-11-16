#include "factory_comandos.h"

FactoryComandos::FactoryComandos(){

}

std::shared_ptr<ComandoMovimiento> FactoryComandos::comando_movimiento(uint8_t dir, uint32_t id){
        return std::make_shared<ComandoMovimiento>(dir,id);
}

// std::shared_ptr<CrearPartida> FactoryComandos::comando_crear_partida(std::string nombre, uint8_t tipo){
//         return std::make_shared<CrearPartida>(tipo,nombre);
// }

std::shared_ptr<DetenerMovimientoCliente> FactoryComandos::comando_detener(uint32_t id){
        return std::make_shared<DetenerMovimientoCliente>(id);
}


std::shared_ptr<EmpezarPartida> FactoryComandos::comando_empezar(){
        return std::make_shared<EmpezarPartida>();
}

FactoryComandos::~FactoryComandos(){

}