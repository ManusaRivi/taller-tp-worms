#ifndef _MENSAJE
#define _MENSAJE
#include "../snapshot.h"
#include "../../common/queue.h"
#include "comando.h"
#include <map>
#include "../mapContainer.h"

#define CREAR_PARTIDA 0x01
#define LISTAR_PARTIDAS 0x02
#define EMPEZAR_PARTIDA 0x03
#define ACCION_JUGADOR 0x04
#define SNAPSHOT 0x05
#define UNIRSE_PARTIDA 0x06
#define LISTAR_MAPAS 0x07

enum COMANDO{
    CMD_CREAR_PARTIDA = CREAR_PARTIDA,
    CMD_LISTAR_PARTIDAS = LISTAR_PARTIDAS,
    CMD_EMPEZAR_PARTIDA = EMPEZAR_PARTIDA,
    CMD_ACCION_JUGADOR = ACCION_JUGADOR,
    CMD_ENVIAR_SNAPSHOT = SNAPSHOT,
    CMD_UNIRSE_PARTIDA = UNIRSE_PARTIDA,
    CMD_LISTAR_MAPAS = LISTAR_MAPAS
};

struct Mensaje{

    bool is_snapshot;
    
    std::map<uint32_t,std::string> lista_mapas;
    Snapshot snap;
    std::shared_ptr<Comando> cmd;
    std::string nombre_mapa;
    uint8_t tipo_comando;
    uint8_t id_partida_a_unirse;
    std::map<uint32_t,std::string> lista_mapas_;

    Mensaje(Snapshot snap);

    Mensaje(std::map<uint32_t,std::string> lista_mapas);
    Mensaje(std::map<uint32_t,std::string> lista_mapas_, bool);

    Mensaje(std::shared_ptr<Comando> cmd);

    Mensaje(std::string nombre_mapa);

    Mensaje();

    uint8_t tipo_mensaje();

    Mensaje(uint8_t tipo);

    Mensaje(uint8_t tipo, uint8_t id);

};

#endif