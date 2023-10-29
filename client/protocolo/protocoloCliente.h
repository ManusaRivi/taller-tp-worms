#ifndef _PROTOCOLO
#define _PROTOCOLO

#include "../../common/socket.h"

#include <iostream>
#include <string>

struct Protocolo{

    const std::string hostname;
    Socket skt;
    bool was_closed;

    explicit Protocolo(const std::string& hostname, const std::string& servname = "http");
    ~Protocolo();

    void enviar_movimiento(uint8_t dir);

};

#endif