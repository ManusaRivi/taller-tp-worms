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
    std::map<uint32_t,std::vector<uint32_t>> id_gusanos_por_player;
    std::map<uint32_t,uint32_t> id_player_por_gusano;


    Partida(uint32_t id_partida, std::string nombre);

    void run() override;

    Snapshot generar_snapshot();

    std::string get_nombre();

    void add_queue(Queue<Mensaje>* snapshots);

    Queue<std::shared_ptr<Comando>>& get_queue();

    uint8_t add_player(uint8_t id_player);

    private:
    void enviar_id_gusanos();

    uint32_t proximo_turno(uint32_t turno_actual);

};

#endif
