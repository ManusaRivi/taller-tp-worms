#include "comando_movimiento.h"



ComandoMovimiento::ComandoMovimiento(uint8_t direccion, uint8_t id):dir(direccion),responsable_id(id){
}


void ComandoMovimiento::agregar_id(uint8_t id){
    responsable_id = id;
}


void ComandoMovimiento::realizar_accion(Mapa &mapa){
    int id;
    int direccion;
    if(id_gusano == 0x00){
        id = 0;
    }
    else{
        id = 1;
    }

    if(dir == 0x01){
        direccion = 0;
    }
    else{
        direccion = 1;
    }
    mapa.MoveWorm(id,direccion);
}