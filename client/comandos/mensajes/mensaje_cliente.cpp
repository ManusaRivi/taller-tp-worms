#include "mensaje_cliente.h"


MensajeCliente::MensajeCliente(uint8_t tipo):tipo_comando(tipo){

}

uint8_t MensajeCliente::get_tipo_comando(){
    return this->tipo_comando;
}