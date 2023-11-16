#ifndef _MensajeCliente_CLIENTE

#define _MensajeCliente_CLIENTE

#include "../game/comunicacion/snapshot.h"
#include "comando.h"
#include <map>

#ifndef TESTING
#define CREAR_PARTIDA 0x01
#define LISTAR_PARTIDAS 0x02
#define EMPEZAR_PARTIDA 0x03
#define ACCION_JUGADOR 0x04
#define SNAPSHOT 0x05
#define PARTIDA_COMENZO 0x06
#define HANDSHAKE 0x07




enum COMANDO{
    CMD_CREAR_PARTIDA = CREAR_PARTIDA,
    CMD_LISTAR_PARTIDAS = LISTAR_PARTIDAS,
    CMD_EMPEZAR_PARTIDA = EMPEZAR_PARTIDA,
    CMD_ACCION_JUGADOR = ACCION_JUGADOR,
    CMD_ENVIAR_SNAPSHOT = SNAPSHOT,
    CMD_PARTIDA_EMPEZO = PARTIDA_COMENZO,
    CMD_HANDSHAKE = HANDSHAKE
};

#endif

struct ComandoCliente;
class SnapshotCliente;

struct MensajeCliente{

    std::shared_ptr<SnapshotCliente> snap;
    uint8_t tipo_comando;

    std::shared_ptr<ComandoCliente> cmd;

    std::string nombre_mapa;
    std::map<uint32_t,std::string> lista_partidas;

    uint32_t id_player;
    std::vector<uint32_t> id_gusanos;

    std::vector<std::vector<float>> vigas;

    

    MensajeCliente(std::shared_ptr<SnapshotCliente> snap);

    MensajeCliente(uint8_t tipo_comando);

    MensajeCliente(std::shared_ptr<ComandoCliente> cmd);

    MensajeCliente(std::map<uint32_t,std::string> mapa);

    MensajeCliente(uint32_t id_player, std::vector<uint32_t> id_gusanos);
    MensajeCliente(uint32_t id_player, std::vector<uint32_t> id_gusanos, std::vector<std::vector<float>> vigas);

};

#endif