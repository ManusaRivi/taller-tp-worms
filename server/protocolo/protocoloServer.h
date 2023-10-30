#ifndef _PROTOCOLO
#define _PROTOCOLO

#include "../../common/socket.h"
#include "../../server/snapshot.h"
#include "../comandos/factory_comandos.h"
#include "../worm.h"

struct Protocolo{

    Socket& skt;

    FactoryComandos factory;

    Protocolo(Socket& skt);

    Comando recibir_comando(bool &was_closed);

    void enviar_snapshot(Snapshot shot);

};

#endif