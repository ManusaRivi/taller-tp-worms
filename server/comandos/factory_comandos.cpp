#include "factory_comandos.h"

FactoryComandos::FactoryComandos(){

}

std::shared_ptr<ComandoMovimiento> FactoryComandos::comando_movimiento(uint8_t dir, uint8_t id){
        return std::make_shared<ComandoMovimiento>(dir,id);
}

// std::shared_ptr<CrearPartida> FactoryComandos::comando_crear_partida(std::string nombre, uint8_t tipo){
//         return std::make_shared<CrearPartida>(tipo,nombre);
// }

std::shared_ptr<DetenerMovimiento> FactoryComandos::comando_detener(){
        return std::make_shared<DetenerMovimiento>();
}

