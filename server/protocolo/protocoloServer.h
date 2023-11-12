#ifndef _PROTOCOLO
#define _PROTOCOLO

#include "../../server/snapshot.h"

#include "../juego/worm.h"
#include "../comandos/mensaje.h"
#include "../../common/protocolo.h"
#include "../comandos/factory_comandos.h"

class FactoryComandos;
struct ServerProtocolo:public Protocolo{

    //Socket& skt;

    FactoryComandos factory;

    ServerProtocolo(Socket& skt);

    Mensaje recibir_comando(bool &was_closed, uint8_t id);

    void enviar_snapshot(Snapshot shot);

    void enviar_partidas(std::map<uint32_t,std::string> lista_mapas);
    
    void partida_empezada();

    void check_partida_empezada();

    void enviar_vigas(Snapshot& snap);

    void enviar_handshake(std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player);

    Mensaje recibir_id_gusanos();
};

#endif