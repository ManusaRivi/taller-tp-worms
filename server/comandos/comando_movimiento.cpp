#include "comando_movimiento.h"



ComandoMovimiento::ComandoMovimiento(uint8_t direccion):Comando(),dir(direccion){
    this->tipo_comando = 0x01;
}


uint8_t ComandoMovimiento::get_direccion(){
    return this->dir;
}