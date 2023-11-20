#ifndef _PROTOCOLO_CLIENTE
#define _PROTOCOLO_CLIENTE

#include "../game/comunicacion/snapshot.h"
#include "../../common/protocolo.h"
#include "../comandos/mensaje.h"
#include "../game/Estados/worm_state_generator.h"

#include <iostream>
#include <string>
#include <map>

struct MensajeCliente;

class ClienteProtocolo:public Protocolo{

    private:
    const std::string hostname;
    bool was_closed;

    public:
    ClienteProtocolo(Socket &peer);
    void detener_movimiento();
    void enviar_movimiento(uint8_t dir);
    std::shared_ptr<MensajeCliente> recibir_snapshot();
    void crear_partida(std::string nombre, uint16_t id);
    void empezar_partida();
    
   
    void unirse_partida(uint32_t id_partida);
    void enviar_handshake(uint32_t id_player, std::vector<uint32_t> id_gusanos);
    bool recibir_comienzo_de_partida();
    void enviar_cambio_de_arma(uint8_t tipo_arma);
    void cambio_angulo(uint8_t direccion_aumento);
    void detener_cambio_angulo();
    void cargar_arma();
    void disparar_arma();
    void enviar_salto(uint8_t direccion_salto);
    void enviar_cambio_direccion_apuntado(uint8_t direccion_apuntado);
    std::map<uint32_t,std::string> pedir_mapas();
    std::map<uint32_t,std::string> pedir_lista_partidas();

    // SE PONEN PUBLICOS PARA TESTING
    std::shared_ptr<MensajeCliente> recibir_handshake();
    std::shared_ptr<MensajeCliente> recibir_snap();

    
    private:
    
    
    std::map<uint32_t,std::string> listar_partidas();
    std::vector<std::vector<float>> recibir_vigas();
    void recibir_gusanos(std::shared_ptr<SnapshotCliente> snap);


};




#endif