#ifndef _PROTOCOLO_SERVER
#define _PROTOCOLO_SERVER

#include "../snapshots/snapshot.h"

#include "../juego/worm.h"
#include "../comandos/mensajes/mensaje.h"
#include "../../common/protocolo.h"
#include "../comandos/factory_comandos.h"
#include "../comandos/mensajes/factory_mensajes.h"
#include "../snapshots/snapshot_partida.h"

class FactoryComandos;
class ServerProtocolo:public Protocolo{

    //Socket& skt;
    private:
    FactoryComandos factory;
    FactoryMensajesServer mensajes;


    public:
    ServerProtocolo(Socket& skt);
    std::shared_ptr<MensajeServer> recibir_comando(bool &was_closed, uint32_t id);
    std::shared_ptr<Comando> recibir_accion(uint32_t id);
    void enviar_snapshot(std::shared_ptr<Snapshot> shot);
    void enviar_partidas(std::map<uint32_t,std::string>& lista_mapas);
    void partida_empezada();
    void check_partida_empezada();
    void enviar_handshake(std::pair<uint32_t,std::vector<uint32_t>>& gusanos_por_player, std::shared_ptr<Snapshot> snap);
    void enviar_mapas(std::map<uint32_t,std::string>& lista_mapas);
    std::shared_ptr<MensajeServer> recibir_id_gusanos();
    void enviar_gusanos(std::vector<WormWrapper>& worms);
    void enviar_estado_unirse(uint8_t estado);
    void enviar_partida_termino(uint32_t equipo_ganador, bool fue_empate);


    // METODOS PUBLICOS PARA TESTEAR
    void enviar_vigas(std::vector<std::vector<float>>& vigas);
    void enviar_lista(std::map<uint32_t,std::string>& lista);
    void enviar_proyectiles(std::vector<ProjectileWrapper>& lista);
    void enviar_explosiones(std::vector<ExplosionWrapper>& lista);
    void enviar_provisiones(std::vector<ProvisionWrapper>& lista);
    void enviar_sonidos(std::vector<SoundTypes>& sonidos);
    void enviar_datos_especiales(std::vector<std::pair<uint8_t,std::vector<float>>>& especiales);
    void enviar_municiones(std::vector<std::pair<int,int>>& municion_armas);                                
    void enviar_carga_actual(uint16_t& carga_actual);
    void enviar_viento(float& viento, bool& es_negativo);
    private:

};

#endif