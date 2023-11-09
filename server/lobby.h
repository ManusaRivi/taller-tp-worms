#ifndef _LOBBY
#define _LOBBY
#include "partida.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "monitorBroadcaster.h"
#include <map>
#include "threads/threadRecibidor.h"
#include "comandos/mensaje.h"

struct Lobby{



    std::map<uint32_t,Partida*> lista_partidas;

    uint32_t id_actual;
    //MonitorClientes &clientes;

    Lobby();

    uint8_t unirse_a_partida(uint32 id, Queue<Mensaje>* snapshots, uint8_t id_player);

    std::pair<uint32_t,uint8_t> crear_partida(std::string nombre_partida, uint8_t creador_responsable,Queue<Mensaje>* snapshots);

    void start_lobby();

    void listar_partidas(Queue<Mensaje>* snapshots);
    void listar_mapas(Queue<Mensaje>* snapshots);

    Queue<std::shared_ptr<Comando>> &get_queue(uint32_t id);

    void empezar_partida(uint32_t id);
    

};

#endif