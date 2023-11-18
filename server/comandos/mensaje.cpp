#include "mensaje.h"


Mensaje::Mensaje(std::map<uint32_t,std::string> lista, uint8_t tipo):is_snapshot(false),lista_mapas(lista),tipo_comando(tipo){

}

Mensaje::Mensaje(Snapshot snapshot):is_snapshot(true),snap(snapshot),tipo_comando(COMANDO::CMD_ENVIAR_SNAPSHOT){

}

Mensaje::Mensaje(std::shared_ptr<Comando> cmd_):cmd(cmd_),tipo_comando(COMANDO::CMD_ACCION_JUGADOR){

}

Mensaje::Mensaje(std::string nombre):nombre_mapa(nombre),tipo_comando(COMANDO::CMD_CREAR_PARTIDA){

}

Mensaje::Mensaje():tipo_comando(COMANDO::CMD_EMPEZAR_PARTIDA){

}

Mensaje::Mensaje(uint8_t tipo):tipo_comando(tipo){}

Mensaje::Mensaje(uint8_t tipo,uint8_t id):tipo_comando(tipo),id_partida_a_unirse(id){

}
Mensaje::Mensaje(std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player_,
                Snapshot snap):snap(snap),tipo_comando(COMANDO::CMD_HANDSHAKE),gusanos_por_player(gusanos_por_player_){

}

Mensaje::Mensaje(std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player_
                ):tipo_comando(COMANDO::CMD_HANDSHAKE),gusanos_por_player(gusanos_por_player_){

}

uint8_t Mensaje::tipo_mensaje(){
    return tipo_comando;
}

