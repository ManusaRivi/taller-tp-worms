#ifndef FACTORY_MENSAJES_SERVER_H
#define FACTORY_MENSAJES_SERVER_H
#include "mensaje_crear_partida.h"
#include "mensaje_empezar_partida.h"
#include "mensaje_handshake_recibir.h"
#include "mensaje_handshake.h"
#include "mensaje_listar_mapas.h"
#include "mensaje_listar_partidas.h"
#include "mensaje_snapshot.h"
#include "mensaje_unirse_partida.h"
#include "mensaje_estado_unirse_partida.h"


class FactoryMensajesServer{

    public:
    FactoryMensajesServer();

    std::shared_ptr<MensajeCrearPartida> crear_partida(std::string nombre_partida, uint16_t id_mapa);
    std::shared_ptr<MensajeEmpezarPartida>  empezar_partida();
    std::shared_ptr<MensajeHandshakeRecibir> handshake_recibir(std::pair<uint32_t,std::vector<uint32_t>> id_gusanos_);
    std::shared_ptr<MensajeHandshakeServer> handshake(std::shared_ptr<Snapshot> snap_,std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player_);
    std::shared_ptr<MensajeListarMapas> listar_mapas(std::map<uint32_t,std::string> lista_);
    std::shared_ptr<MensajeListarPartidas>  listar_partidas(std::map<uint32_t,std::string> lista_);
    std::shared_ptr<MensajeSnapshotServer> snapshot(std::shared_ptr<Snapshot> snap_);
    std::shared_ptr<MensajeUnirsePartida> unirse_partida(uint32_t id_partida);
    std::shared_ptr<MensajeListarMapas> listar_mapas_recibidor();
    std::shared_ptr<MensajeListarPartidas> listar_partidas_recibidor();
    std::shared_ptr<MensajeEstadoUnirse> estado_unirse_partida(uint8_t estado);

};

#endif