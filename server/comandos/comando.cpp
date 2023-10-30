#include "comando.h"


Comando::Comando(uint8_t dir_, uint8_t tipo):tipo_comando(tipo),dir(dir_){

}

uint8_t Comando::get_direccion(){
    return this->dir;
}

void Comando::agregar_id(uint8_t id){
    this->responsable_id = id;
}

uint8_t Comando::get_tipo(){
        return this->tipo_comando;
}