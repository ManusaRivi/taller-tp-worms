#include "factory_comandos.h"

FactoryComandos::FactoryComandos(){

}

std::shared_ptr<ComandoMovimiento> FactoryComandos::comando_movimiento(uint8_t dir, uint32_t id){
        return std::make_shared<ComandoMovimiento>(dir,id);
}

// std::shared_ptr<CrearPartida> FactoryComandos::comando_crear_partida(std::string nombre, uint8_t tipo){
//         return std::make_shared<CrearPartida>(tipo,nombre);
// }

std::shared_ptr<DetenerMovimiento> FactoryComandos::comando_detener(uint32_t id){
        return std::make_shared<DetenerMovimiento>(id);
}




std::shared_ptr<EmpezarPartida> FactoryComandos::comando_empezar(){
        return std::make_shared<EmpezarPartida>();
}

std::shared_ptr<CambiarAngulo> FactoryComandos::comando_cambiar_angulo(uint32_t id, uint8_t dir){
        return std::make_shared<CambiarAngulo>(dir,id);
}

std::shared_ptr<Disparar> FactoryComandos::comando_disparar(uint32_t id){
        return std::make_shared<Disparar>(id);
}

std::shared_ptr<CambiarArma> FactoryComandos::comando_cambiar_arma(uint32_t id, uint8_t tipo_arma){
        return std::make_shared<CambiarArma>(tipo_arma,id);
}

std::shared_ptr<Saltar> FactoryComandos::comando_saltar(uint32_t id, uint8_t dir){
        return std::make_shared<Saltar>(dir,id);
}

std::shared_ptr<CargarArma> FactoryComandos::comando_cargar_arma(uint32_t id){
        return std::make_shared<CargarArma>(id);
}

std::shared_ptr<DetenerAngulo> FactoryComandos::comando_detener_angulo(uint32_t id){
        return std::make_shared<DetenerAngulo>(id);
}

std::shared_ptr<CambiarDireccionArma> FactoryComandos::comando_cambia_direccion_arma(uint32_t id, uint8_t dir){
        return std::make_shared<CambiarDireccionArma>(dir,id);
}

std::shared_ptr<SetearTarget> FactoryComandos::comando_setear_target(uint32_t id, float x, float y){
        return std::make_shared<SetearTarget>(x,y,id );
}

std::shared_ptr<SetearTimer> FactoryComandos::comando_setear_timer(uint32_t id, uint32_t time){
        return std::make_shared<SetearTimer>(time,id);
}

std::shared_ptr<ActivarCheat> FactoryComandos::comando_activar_cheat(uint32_t id,uint8_t tipo){
        return std::make_shared<ActivarCheat>(tipo,id);
}



FactoryComandos::~FactoryComandos(){

}