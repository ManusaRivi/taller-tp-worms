#include "comando.h"



Comando::Comando(){

}

void Comando::agregar_direccion(uint8_t dir){
    this->dir = dir;
}

void Comando::agregar_tipo(uint8_t tipo){
    this->tipo_comando = tipo;
}
