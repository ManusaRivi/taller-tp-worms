#include "mensaje_handshake.h"

MensajeHandshakeServer::MensajeHandshakeServer(std::shared_ptr<Snapshot> snap_,std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player_):MensajeServer(COMANDO::CMD_HANDSHAKE),gusanos_por_player(gusanos_por_player_),snap(snap_){

}


    std::shared_ptr<Snapshot>& MensajeHandshakeServer::get_snap(){
        return this->snap;
    }
    std::pair<uint32_t,std::vector<uint32_t>>& MensajeHandshakeServer::get_gusanos_por_player_(){
        return this->gusanos_por_player;
    }