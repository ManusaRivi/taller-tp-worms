#ifndef MENSAJES_CLIENTES
#define MENSAJES_CLIENTES
#include <iostream>


#ifndef TESTING
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

#endif



class MensajeCliente{

    uint8_t tipo_comando;

    public:
    MensajeCliente(uint8_t tipo_comando);

    uint8_t get_tipo_comando();

    virtual ~MensajeCliente() = default;

};

#endif
