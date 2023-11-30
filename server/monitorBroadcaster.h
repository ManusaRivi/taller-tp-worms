#ifndef _Broadcaster
#define _Broadcaster
#include "../../common/queue.h"
#include "snapshots/snapshot.h"
#include <list>
#include "comandos/mensajes/factory_mensajes.h"

struct BroadCaster{

    std::list<Queue<std::shared_ptr<MensajeServer>>*> lista;
    FactoryMensajesServer mensajes;
    std::mutex lck;

    BroadCaster();

    void add_queue(Queue<std::shared_ptr<MensajeServer>>* q);

    void broadcastSnap(std::shared_ptr<MensajeServer> snap);

    uint32_t cantidad_jugadores();

    void informar_primer_snapshot(std::map<uint32_t,std::vector<uint32_t>> gusanos_por_player, std::shared_ptr<SnapshotHandshake> snap);

    void remover_player(Queue<std::shared_ptr<MensajeServer>>* q);

};

#endif