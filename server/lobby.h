#ifndef _LOBBY
#define _LOBBY
#include "partida.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "monitorBroadcaster.h"
#include <map>
#include "threads/threadRecibidor.h"
#include "comandos/mensajes/factory_mensajes.h"
#include "mapContainer.h"

class Lobby {
    MapContainer& lista_mapas;
    std::map<uint32_t,Partida*> lista_partidas;
    FactoryMensajesServer mensajes;
    uint32_t id_actual;
    std::mutex lck;
    //MonitorClientes &clientes;

    public:
    Lobby(MapContainer& mapas);
    void unirse_a_partida(uint32 id, Queue<std::shared_ptr<MensajeServer>>* snapshots);
    uint32_t crear_partida(std::string nombre_partida, Queue<std::shared_ptr<MensajeServer>>* snapshots, uint16_t id_mapa);
    std::map<uint32_t,std::string> listar_partidas(Queue<std::shared_ptr<MensajeServer>>* cliente);
    Queue<std::shared_ptr<Comando>> &get_queue(uint32_t id);
    std::map<uint32_t,std::string> listar_mapas(Queue<std::shared_ptr<MensajeServer>>* cliente);
    void desconectarse_partida(uint32_t id, Queue<std::shared_ptr<MensajeServer>>* snapshots);
    void kill();

    private:
    void start_lobby();
    void empezar_partida(uint32_t id);
};

#endif