#ifndef _PROTOCOLO
#define _PROTOCOLO

#include "../../server/snapshot.h"

#include "../juego/worm.h"
#include "../comandos/mensaje.h"
#include "../../common/protocolo.h"
#include "../comandos/factory_comandos.h"

class FactoryComandos;
class ServerProtocolo:public Protocolo{

    //Socket& skt;
    private:
    FactoryComandos factory;

    public:
    ServerProtocolo(Socket& skt);
    Mensaje recibir_comando(bool &was_closed, uint32_t id);
    std::shared_ptr<Comando> recibir_accion(uint32_t id);
    void enviar_snapshot(Snapshot shot);
    void enviar_partidas(std::map<uint32_t,std::string> lista_mapas);
    void partida_empezada();
    void check_partida_empezada();
    void enviar_handshake(std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player, Snapshot snap);
    void enviar_mapas(std::map<uint32_t,std::string> lista_mapas);

    Mensaje recibir_id_gusanos();
    private:
    void enviar_vigas(std::vector<std::vector<float>> vigas);
    void enviar_lista(std::map<uint32_t,std::string> lista);
    void enviar_gusanos(Snapshot snap);


};

#endif