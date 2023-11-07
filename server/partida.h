#ifndef _PARTIDA
#define _PARTIDA

#include "../common/queue.h"
#include "comandos/comando.h"
#include "../common/thread.h"
#include "juego/mapa.h"
#include "monitorBroadcaster.h"
#include "comandos/comando_movimiento.h"

struct Partida:public Thread{

    Queue<std::shared_ptr<Comando>> acciones_a_realizar;
    Mapa mapa;
    BroadCaster broadcaster;
    uint32_t id_partida;
    std::string nombre_partida;
    std::vector<uint8_t> posibles_id_gusanos;
    std::map<uint8_t,std::vector<uint8_t>> vector_gusanos_player;

    Partida(uint32_t id_partida, std::string nombre);

    void run() override;

    Snapshot generar_snapshot();

    std::string get_nombre();

    void add_queue(Queue<Mensaje>* snapshots);

    Queue<std::shared_ptr<Comando>>& get_queue();

    uint8_t add_player(uint8_t id_player);

};

#endif
