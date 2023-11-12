#include "comando_empezar_partida.h"
#include "mensaje.h"


EmpezarPartida::EmpezarPartida():tipo_de_comando(COMANDO::CMD_EMPEZAR_PARTIDA){

}


void EmpezarPartida::realizar_accion(Mapa &mapa){
}

uint8_t EmpezarPartida::get_comando(){
    return this->tipo_de_comando;
}

void EmpezarPartida::agregar_id(uint8_t id){
    
}