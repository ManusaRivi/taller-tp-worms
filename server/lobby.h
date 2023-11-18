#ifndef _LOBBY
#define _LOBBY
#include "partida.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "monitorBroadcaster.h"
#include <map>
#include "threads/threadRecibidor.h"
#include "comandos/mensaje.h"

class Lobby {
    MapContainer lista_mapas;
    std::map<uint32_t,Partida*> lista_partidas;

    uint32_t id_actual;
    std::mutex lck;
    //MonitorClientes &clientes;

    public:
    Lobby();
    void unirse_a_partida(uint32 id, Queue<Mensaje>* snapshots);
    uint32_t crear_partida(std::string nombre_partida, Queue<Mensaje>* snapshots);
    void listar_partidas(Queue<Mensaje>* cliente);
    Queue<std::shared_ptr<Comando>> &get_queue(uint32_t id);
    void listar_mapas(Queue<Mensaje>* cliente);
    void desconectarse_partida(uint32_t id, Queue<Mensaje>* snapshots);
    void kill();

    private:
    void start_lobby();
    void empezar_partida(uint32_t id);
};

#endif