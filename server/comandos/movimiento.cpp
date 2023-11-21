#include "movimiento.h"



ComandoMovimiento::ComandoMovimiento(uint8_t direccion, uint32_t id):Comando(id),dir(direccion){
}




void ComandoMovimiento::realizar_accion(Mapa* mapa){
    int direccion;

    if(dir == 0x01){
        direccion = 0;
    }
    else{
        direccion = 1;
    }
    mapa->MoveWorm(this->get_responsable(),direccion);
}

