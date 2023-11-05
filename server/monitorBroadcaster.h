#ifndef _Broadcaster
#define _Broadcaster
#include "../../common/queue.h"
#include "snapshot.h"
#include <list>
#include "comandos/mensaje.h"

struct BroadCaster{

    std::list<Queue<Mensaje>*> lista;

    BroadCaster();

    void add_queue(Queue<Mensaje>* q);

    void broadcastSnap(Mensaje snap);

};

#endif