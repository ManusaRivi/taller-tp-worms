#include "mensaje_estado_unirse_partida.h"


MensajeEstadoUnirse::MensajeEstadoUnirse(uint8_t estado_):MensajeServer(COMANDO::CMD_ESTADO_UNIRSE),estado(estado_){

}

uint8_t MensajeEstadoUnirse::get_state(){
    return this->estado;
}