#ifndef _CREAR_PARTIDA
#define _CREAR_PARTIDA
#include "comando.h"
#include "../lobby.h"


struct Lobby;
struct CrearPartida:public Comando{

    std::string nombre_partida;
    uint8_t tipo_de_comando;

    CrearPartida(uint8_t tipo, std::string nombre);

    uint32_t realizar_accion(Lobby &lobby, Queue<Mensaje>* snapshots, uint8_t responsable);
};

#endif