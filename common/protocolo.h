#ifndef PROTOCOLO_MAIN
#define PROTOCOLO_MAIN
#ifdef TESTING
#include "../tests/test_socket.h"
#else
#include "socket.h"
#endif
#include <iostream>
#include <arpa/inet.h>
#include <vector>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include "liberror.h"

#define CODIGO_MOVER 0x01
#define CODIGO_DETENER_MOVIMIENTO 0x02
#define CODIGO_CREAR_PARTIDA 0x03
#define CODIGO_EMPEZAR_PARTIDA 0x04
#define CODIGO_LISTAR_PARTIDA 0x05
#define CODIGO_PARTIDA_POR_COMENZAR 0x06
#define CODIGO_UNIRSE_PARTIDA 0x07
#define CODIGO_HANDSHAKE_EMPEZAR_PARTIDA 0x08
#define CODIGO_SNAPSHOT 0x10
#define CODIGO_CAMBIAR_ANGULO 0x11
#define CODIGO_CARGAR_ARMA 0x12
#define CODIGO_DISPARAR 0x13
#define CODIGO_SALTAR 0x14
#define CODIGO_DETENER_CAMBIO_ANGULO 0x15
#define CODIGO_CAMBIAR_ARMA 0x16
#define CODIGO_RECIBIR_VIGAS 0x17
#define CODIGO_LISTAR_MAPAS 0x18


#define SIZE_DOS 2
#define SIZE_UNO 1
#define SIZE_CUATRO 4

struct ClosedSocket:public std::exception{
    public:
    ClosedSocket(){
    } 
};

class Protocolo{

    public:
    Socket &skt;

    Protocolo(Socket &skt);

    void enviar_4_bytes_float(float num);

    void enviar_4_bytes(uint32_t num);

    void enviar_1_byte(uint8_t num);

    void enviar_string(std::string);

    void enviar_2_byte(uint16_t num);

    std::string recibir_string();

    uint32_t recibir_4_bytes();

    uint16_t recibir_2_bytes();

    uint8_t recibir_1_byte();

    float recibir_4_bytes_float();

};

#endif