#include "comando_movimiento.h"



ComandoMovimiento::ComandoMovimiento(uint8_t direccion, uint32_t id):Comando(id),dir(direccion){
}


void ComandoMovimiento::agregar_id(uint8_t id){
    responsable_id = id;
}


void ComandoMovimiento::realizar_accion(Mapa &mapa,uint32_t id){
    int direccion;

    if(dir == 0x01){
        direccion = 0;
    }
    else{
        direccion = 1;
    }
    mapa.MoveWorm(id,direccion);
}

uint8_t ComandoMovimiento::get_comando(){
    return this->tipo_comando;
}