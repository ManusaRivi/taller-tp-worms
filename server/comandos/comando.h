#ifndef _COMANDO_SERVER
#define _COMANDO_SERVER

#include <iostream>
#include "../juego/mapa.h"


enum ESTADO{
    WALKING = 1,
    SALTANDO = 3,
    CAYENDO = 4, 
    HOLDING_BAZOOKA = 5,
    HOLDING_DINAMITA = 9,
    HOLDING_SANTA = 12,
    HOLDING_VERDE = 14,
    HOLDING_BANANA = 16,
    HOLDING_ROJA = 18
};



#define CREAR_PARTIDA 0x01
#define LISTAR_PARTIDAS 0x02
#define EMPEZAR_PARTIDA 0x03
#define ACCION_JUGADOR 0x04
#define SNAPSHOT 0x05
#define UNIRSE_PARTIDA 0x06
#define HANDSHAKE 0x07
#define LISTAR_MAPAS 0x08
#define ESTADO_UNIRSE 0x10

enum COMANDO{
    CMD_CREAR_PARTIDA = CREAR_PARTIDA,
    CMD_LISTAR_PARTIDAS = LISTAR_PARTIDAS,
    CMD_EMPEZAR_PARTIDA = EMPEZAR_PARTIDA,
    CMD_ACCION_JUGADOR = ACCION_JUGADOR,
    CMD_ENVIAR_SNAPSHOT = SNAPSHOT,
    CMD_UNIRSE_PARTIDA = UNIRSE_PARTIDA,
    CMD_HANDSHAKE = HANDSHAKE,
    CMD_LISTAR_MAPAS = LISTAR_MAPAS,
    CMD_ESTADO_UNIRSE = ESTADO_UNIRSE
};


class Comando{

    uint32_t responsable_id;
    uint32_t tipo_comando;

    public:
    Comando();

    Comando(uint32_t id);


    virtual void realizar_accion(Mapa& mapa) = 0;

    uint32_t get_responsable();

    uint32_t get_comando();

    virtual ~Comando() = default;


};

#endif