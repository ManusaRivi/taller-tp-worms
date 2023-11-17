#ifndef _Broadcaster
#define _Broadcaster
#include "../../common/queue.h"
#include "snapshot.h"
#include <list>
#include "comandos/mensaje.h"

struct BroadCaster{

    std::list<Queue<Mensaje>*> lista;
    std::mutex lck;

    BroadCaster();

    void add_queue(Queue<Mensaje>* q);

    void broadcastSnap(Mensaje snap);

    uint16_t cantidad_jugadores();

    void informar_primer_snapshot(std::map<uint32_t,std::vector<uint32_t>> gusanos_por_player,std::vector<std::vector<float>> vigas);

    void remover_player(Queue<Mensaje>* q);

};

#endif