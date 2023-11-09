#include "mensaje.h"


Mensaje::Mensaje(std::map<uint32_t,std::string> lista):is_snapshot(false),lista_mapas(lista),snap(std::vector<std::vector<int>>()),tipo_comando(COMANDO::CMD_LISTAR_PARTIDAS){

}

Mensaje::Mensaje(Snapshot snapshot):is_snapshot(true),snap(snapshot),tipo_comando(COMANDO::CMD_ENVIAR_SNAPSHOT){

}

Mensaje::Mensaje(std::shared_ptr<Comando> cmd_):snap(std::vector<std::vector<int>>()),cmd(cmd_),tipo_comando(COMANDO::CMD_ACCION_JUGADOR){

}

Mensaje::Mensaje(std::string nombre):snap(std::vector<std::vector<int>>()),nombre_mapa(nombre),tipo_comando(COMANDO::CMD_CREAR_PARTIDA){

}

Mensaje::Mensaje():snap(std::vector<std::vector<int>>()),tipo_comando(COMANDO::CMD_EMPEZAR_PARTIDA){

}

Mensaje::Mensaje(std::map<uint32_t,std::string> mapas, bool b):snap(std::vector<std::vector<int>>()),tipo_comando(COMANDO::CMD_LISTAR_MAPAS),lista_mapas_(mapas){

}


Mensaje::Mensaje(uint8_t tipo):snap(std::vector<std::vector<int>>()),tipo_comando(tipo){}

Mensaje::Mensaje(uint8_t tipo,uint8_t id):snap(std::vector<std::vector<int>>()),tipo_comando(tipo),id_partida_a_unirse(id){

}

uint8_t Mensaje::tipo_mensaje(){
    return tipo_comando;
}

