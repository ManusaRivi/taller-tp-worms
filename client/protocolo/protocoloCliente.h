#ifndef _PROTOCOLO
#define _PROTOCOLO

#include "../../common/socket.h"
#include "../snapshot.h"

#include <iostream>
#include <string>

struct Protocolo{

    const std::string hostname;
    Socket &skt;
    bool was_closed;

    explicit Protocolo(Socket &peer);
    ~Protocolo();

    void enviar_movimiento(uint8_t dir);

    Snapshot recibir_snapshot();

    void detener_movimiento();


};




#endif