#ifndef _PROTOCOLO
#define _PROTOCOLO

#include "../../common/socket.h"
#include "../game/comunicacion/snapshot.h"
#include "../../common/protocolo.h"
#include "../comandos/mensaje.h"

#include <iostream>
#include <string>
#include <map>

struct Mensaje;

struct ClienteProtocolo:public Protocolo{

    const std::string hostname;
    bool was_closed;

    ClienteProtocolo(Socket &peer);

    void enviar_movimiento(uint8_t dir);

    Mensaje recibir_snapshot();

    void detener_movimiento();

    void crear_partida(std::string nombre);

    void empezar_partida();

    std::map<uint32_t,std::string> listar_partidas();
    std::map<uint32_t,std::string> listar_mapas();

    void pedir_lista_partidas();
    void pedir_lista_mapas();

    void unirse_partida(std::string id_paritda);


};




#endif