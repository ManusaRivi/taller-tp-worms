#ifndef _PROTOCOLO
#define _PROTOCOLO

#include "../game/comunicacion/snapshot.h"
#include "../../common/protocolo.h"
#include "../comandos/mensaje.h"
#include "../game/Estados/worm_state_generator.h"

#include <iostream>
#include <string>
#include <map>

struct Mensaje;

struct ClienteProtocolo:public Protocolo{

    const std::string hostname;
    bool was_closed;

    ClienteProtocolo(Socket &peer);

    void enviar_movimiento(uint8_t dir);

    std::shared_ptr<Mensaje> recibir_snapshot();

    void detener_movimiento();

    void crear_partida(std::string nombre);

    void empezar_partida();

    std::map<uint32_t,std::string> listar_partidas();

    void pedir_lista_partidas();

    void unirse_partida(std::string id_paritda);

    std::shared_ptr<Mensaje> recibir_id_gusanos();

    void enviar_handshake(uint32_t id_player, std::vector<uint32_t> id_gusanos);

    std::shared_ptr<Mensaje> recibir_snap();


};




#endif