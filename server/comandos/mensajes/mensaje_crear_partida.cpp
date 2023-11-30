#include "mensaje_crear_partida.h"

MensajeCrearPartida::MensajeCrearPartida(std::string partida, uint16_t id_mapa_):MensajeServer(COMANDO::CMD_CREAR_PARTIDA),nombre_partida(partida),id_mapa(id_mapa_){

}


    std::string& MensajeCrearPartida::get_nombre_partida(){
        return this->nombre_partida;
    }
    uint16_t& MensajeCrearPartida::get_id_mapa(){
        return this->id_mapa;
    }