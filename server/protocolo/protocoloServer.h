#ifndef _PROTOCOLO
#define _PROTOCOLO

#include "../../common/socket.h"
#include "../../server/snapshot.h"
#include "../comandos/factory_comandos.h"
#include "../juego/worm.h"

struct Protocolo{

    Socket& skt;

    FactoryComandos factory;

    Protocolo(Socket& skt);

    std::shared_ptr<Comando> recibir_comando(bool &was_closed, uint8_t id);

    void enviar_snapshot(Snapshot shot);

};

#endif