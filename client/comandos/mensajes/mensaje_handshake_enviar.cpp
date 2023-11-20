#include "mensaje_handshake_enviar.h"

MensajeHandshakeEnviar::MensajeHandshakeEnviar(uint32_t id_player_, std::vector<uint32_t> id_gusanos_):MensajeCliente(COMANDO::CMD_HANDSHAKE),id_player(id_player_),id_gusanos(id_gusanos_){

}


    uint32_t MensajeHandshakeEnviar::get_player(){
        return this->id_player;
    }

    std::vector<uint32_t> MensajeHandshakeEnviar::get_gusanos(){
        return this->id_gusanos;
    }