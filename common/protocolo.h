#include "socket.h"
#include <iostream>
#include <arpa/inet.h>
#include <vector>
#include <string.h>
#include <sstream>
#include <stdio.h>

#define CODIGO_MOVIMIENTO 0x01
#define CODIGO_CREAR_PARTIDA 0x02
#define CODIGO_EMPEZAR_PARTIDA 0x03
#define CODIGO_LISTAR_PARTIDA 0x04
#define CODIGO_PARTIDA_POR_COMENZAR 0x05
#define CODIGO_UNIRSE_PARTIDA 0x06


#define SIZE_DOS 2
#define SIZE_UNO 1
#define SIZE_CUATRO 4



struct Protocolo{

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

};