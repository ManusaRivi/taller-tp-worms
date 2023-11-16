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
#define HANDSHAKE 0x07
#define LISTAR_MAPAS 0x08

enum COMANDO{
    CMD_CREAR_PARTIDA = CREAR_PARTIDA,
    CMD_LISTAR_PARTIDAS = LISTAR_PARTIDAS,
    CMD_EMPEZAR_PARTIDA = EMPEZAR_PARTIDA,
    CMD_ACCION_JUGADOR = ACCION_JUGADOR,
    CMD_ENVIAR_SNAPSHOT = SNAPSHOT,
    CMD_PARTIDA_EMPEZO = PARTIDA_COMENZO,
    CMD_HANDSHAKE = HANDSHAKE,
    CMD_LISTAR_MAPAS = LISTAR_MAPAS
};

struct Comando;

struct Mensaje{

    std::shared_ptr<Snapshot> snap;
    uint8_t tipo_comando;

    std::shared_ptr<Comando> cmd;

    std::string nombre_mapa;
    std::map<uint32_t,std::string> lista_partidas;

    uint32_t id_player;
    std::vector<uint32_t> id_gusanos;

    

    Mensaje(std::shared_ptr<Snapshot> snap);

    Mensaje(uint8_t tipo_comando);

    Mensaje(std::shared_ptr<Comando> cmd);

    Mensaje(std::map<uint32_t,std::string> mapa);

    Mensaje(uint32_t id_player, std::vector<uint32_t> id_gusanos);

};

#endif