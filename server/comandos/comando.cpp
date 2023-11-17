#include "comando.h"



Comando::Comando(){

}

Comando::Comando(uint32_t id):responsable_id(id){

}


uint32_t Comando::get_responsable(){
    return this->responsable_id;
}
