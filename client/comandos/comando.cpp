#include "comando.h"



ComandoCliente::ComandoCliente(){

}

void ComandoCliente::agregar_direccion(uint8_t dir){
    this->dir = dir;
}

void ComandoCliente::agregar_tipo(uint8_t tipo){
    this->tipo_comando = tipo;
}
