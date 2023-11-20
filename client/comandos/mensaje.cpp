#include "mensaje.h"


MensajeCliente::MensajeCliente(std::shared_ptr<SnapshotCliente> snap_):snap(snap_),tipo_comando(COMANDO::CMD_ENVIAR_SNAPSHOT){

}

MensajeCliente::MensajeCliente(uint8_t tipo):tipo_comando(tipo){

}

MensajeCliente::MensajeCliente(std::shared_ptr<ComandoCliente> cmd_):tipo_comando(COMANDO::CMD_ACCION_JUGADOR),cmd(cmd_){

}


MensajeCliente::MensajeCliente(std::map<uint32_t,std::string> mapa_):tipo_comando(COMANDO::CMD_LISTAR_PARTIDAS),lista_partidas(mapa_){

}

MensajeCliente::MensajeCliente(uint32_t id_player_, std::vector<uint32_t> id_gusanos_):tipo_comando(COMANDO::CMD_HANDSHAKE),id_player(id_player_),id_gusanos(id_gusanos_){

}

MensajeCliente::MensajeCliente(uint32_t id_player_, std::vector<uint32_t> id_gusanos_,std::shared_ptr<World> world_):tipo_comando(COMANDO::CMD_HANDSHAKE),id_player(id_player_),id_gusanos(id_gusanos_), world(world_){

}


// FUNCION SOLO PARA TESTING

std::shared_ptr<SnapshotCliente> MensajeCliente::get_snap(){
    return std::move(this->snap);
}