#ifndef _PROTOCOLO
#define _PROTOCOLO

#include "../../common/socket.h"
#include "../../server/snapshot.h"
#include "../comandos/factory_comandos.h"
#include "../juego/worm.h"
#include "../comandos/mensaje.h"
#include "../../common/protocolo.h"

struct ServerProtocolo:public Protocolo{

    //Socket& skt;

    FactoryComandos factory;

    ServerProtocolo(Socket& skt);

    Mensaje recibir_comando(bool &was_closed, uint8_t id);

    void enviar_snapshot(Snapshot shot);

    void enviar_partidas(std::map<uint32_t,std::string> lista_mapas);
    void enviar_mapas(std::map<uint32_t,std::string> map);
    void partida_empezada();

    void check_partida_empezada();

};

#endif