#include "monitorBroadcaster.h"


BroadCaster::BroadCaster(){

}

void BroadCaster::add_queue(Queue<Snapshot>* q){
    lista.push_back(q);
}

void BroadCaster::broadcastSnap(Snapshot snap){
    for (auto& c: lista) {
        c->push(snap);
    }
}