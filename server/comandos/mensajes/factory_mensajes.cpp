#include "factory_mensajes.h" 

using namespace std;
    FactoryMensajesServer::FactoryMensajesServer(){

    }

    std::shared_ptr<MensajeCrearPartida> FactoryMensajesServer::crear_partida(std::string nombre_partida, uint16_t id_mapa){
        return make_shared<MensajeCrearPartida>(nombre_partida,id_mapa);
    }
    std::shared_ptr<MensajeEmpezarPartida>  FactoryMensajesServer::empezar_partida(){
        return make_shared<MensajeEmpezarPartida>();
    }
    std::shared_ptr<MensajeHandshakeRecibir> FactoryMensajesServer::handshake_recibir(std::pair<uint32_t,std::vector<uint32_t>> id_gusanos_){
        return make_shared<MensajeHandshakeRecibir>(id_gusanos_);
    }
    std::shared_ptr<MensajeHandshakeServer> FactoryMensajesServer::handshake(std::shared_ptr<Snapshot> snap_,std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player_){
        return make_shared<MensajeHandshakeServer>(snap_,gusanos_por_player_);
    }
    std::shared_ptr<MensajeListarMapas> FactoryMensajesServer::listar_mapas(std::map<uint32_t,std::string> lista_){
        return make_shared<MensajeListarMapas>(lista_);
    }
    std::shared_ptr<MensajeListarPartidas>  FactoryMensajesServer::listar_partidas(std::map<uint32_t,std::string> lista_){
        return make_shared<MensajeListarPartidas>(lista_);
    }
    std::shared_ptr<MensajeSnapshotServer> FactoryMensajesServer::snapshot(std::shared_ptr<Snapshot> snap_){
        return make_shared<MensajeSnapshotServer>(snap_);
    }
    std::shared_ptr<MensajeUnirsePartida> FactoryMensajesServer::unirse_partida(uint32_t id_partida){
        return make_shared<MensajeUnirsePartida>(id_partida);
    }

     std::shared_ptr<MensajeListarMapas> FactoryMensajesServer::listar_mapas_recibidor(){
        return make_shared<MensajeListarMapas>();
     }
     std::shared_ptr<MensajeListarPartidas> FactoryMensajesServer::listar_partidas_recibidor(){
        return make_shared<MensajeListarPartidas>();
     }