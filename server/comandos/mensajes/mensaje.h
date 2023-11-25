#ifndef MENSAJES_SERVER_H
#define MENSAJES_SERVER_H
#include <map>
#include <vector>
#include <iostream>
#include "../comando.h"


class MensajeServer{
    uint8_t tipo_mensaje;
    public:
    MensajeServer(uint8_t tipo);

    uint8_t get_tipo();

    virtual ~MensajeServer() = default;


};

#endif