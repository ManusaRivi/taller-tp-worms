#include "mensaje.h"

MensajeServer::MensajeServer(uint8_t tipo):tipo_mensaje(tipo){
    
}


uint8_t MensajeServer::get_tipo(){
    return this->tipo_mensaje;
}