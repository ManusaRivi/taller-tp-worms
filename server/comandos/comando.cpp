#include "comando.h"



Comando::Comando():tipo_comando(3){

}

Comando::Comando(uint32_t id):responsable_id(id){

}


uint32_t Comando::get_responsable(){
    return this->responsable_id;
}

uint32_t Comando::get_comando(){
    return this->tipo_comando;
}
