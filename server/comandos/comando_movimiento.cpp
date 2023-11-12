#include "comando_movimiento.h"



ComandoMovimiento::ComandoMovimiento(uint8_t direccion, uint8_t id):dir(direccion),responsable_id(id){
}


void ComandoMovimiento::agregar_id(uint8_t id){
    responsable_id = id;
}


void ComandoMovimiento::realizar_accion(Mapa &mapa,uint32_t id){
    int idx;
    int direccion;
    if(id == 1){
        idx = 0;
    }
    else{
        idx = 1;
    }

    if(dir == 0x01){
        direccion = 0;
    }
    else{
        direccion = 1;
    }
    mapa.MoveWorm(idx,direccion);
}

uint8_t ComandoMovimiento::get_comando(){
    return this->tipo_comando;
}