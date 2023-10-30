#ifndef _Broadcaster
#define _Broadcaster
#include "../../common/queue.h"
#include "../../client/snapshot.h"
#include <list>

struct BroadCaster{

    std::list<Queue<Snapshot>*> lista;

    BroadCaster();

    void add_queue(Queue<Snapshot>* q);

    void broadcastSnap(Snapshot snap);

};

#endif