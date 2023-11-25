#include "mensaje_unirse_partida.h"

MensajeUnirsePartida::MensajeUnirsePartida(uint32_t id_part):MensajeServer(COMANDO::CMD_UNIRSE_PARTIDA),id_partida(id_part){

}


uint32_t MensajeUnirsePartida::get_id_partida(){
    return this->id_partida;
}