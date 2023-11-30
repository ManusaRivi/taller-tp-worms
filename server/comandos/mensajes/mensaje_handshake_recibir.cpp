#include "mensaje_handshake_recibir.h"

MensajeHandshakeRecibir::MensajeHandshakeRecibir(std::pair<uint32_t,std::vector<uint32_t>> id_gusanos_):MensajeServer(COMANDO::CMD_HANDSHAKE),id_gusanos(id_gusanos_){
    
}



std::pair<uint32_t,std::vector<uint32_t>>& MensajeHandshakeRecibir::get_pair(){
    return this->id_gusanos;
}