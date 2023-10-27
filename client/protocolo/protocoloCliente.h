#ifndef _PROTOCOLO
#define _PROTOCOLO
#include "../../common/socket.h"
#include <iostream>

struct Protocolo{

    Socket& skt;

    Protocolo(Socket& skt);

    void enviar_movimiento(uint8_t dir);

};

#endif