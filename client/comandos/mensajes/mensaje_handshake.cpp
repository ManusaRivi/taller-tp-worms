#include "mensaje_handshake.h"


MensajeHandshake::MensajeHandshake(uint32_t id_player_, std::vector<uint32_t> id_gusanos_,std::shared_ptr<World> world_):MensajeCliente(COMANDO::CMD_HANDSHAKE),id_player(id_player_),id_gusanos(id_gusanos_), world(world_){

}

    uint32_t MensajeHandshake::get_id(){
        return  this->id_player;

    }
    std::vector<uint32_t> MensajeHandshake::get_gusanos(){
        return this->id_gusanos;
    }
    std::shared_ptr<World> MensajeHandshake::get_world(){
        return this->world;
    }