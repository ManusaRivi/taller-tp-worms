#ifndef _MENSAJE

#define _MENSAJE

#include "../game/comunicacion/snapshot.h"
#include "comando.h"
#include <map>

#define CREAR_PARTIDA 0x01
#define LISTAR_PARTIDAS 0x02
#define EMPEZAR_PARTIDA 0x03
#define ACCION_JUGADOR 0x04
#define SNAPSHOT 0x05
#define PARTIDA_COMENZO 0x06



enum COMANDO{
    CMD_CREAR_PARTIDA = CREAR_PARTIDA,
    CMD_LISTAR_PARTIDAS = LISTAR_PARTIDAS,
    CMD_EMPEZAR_PARTIDA = EMPEZAR_PARTIDA,
    CMD_ACCION_JUGADOR = ACCION_JUGADOR,
    CMD_ENVIAR_SNAPSHOT = SNAPSHOT,
    CMD_PARTIDA_EMPEZO = PARTIDA_COMENZO
};

struct Comando;

struct Mensaje{

    Snapshot snap;
    uint8_t tipo_comando;

    std::shared_ptr<Comando> cmd;

    std::string nombre_mapa;
    std::map<uint32_t,std::string> lista_partidas;

    

    Mensaje(Snapshot snap);

    Mensaje(uint8_t tipo_comando);

    Mensaje(std::shared_ptr<Comando> cmd);

    Mensaje(std::map<uint32_t,std::string> mapa);

};

#endif