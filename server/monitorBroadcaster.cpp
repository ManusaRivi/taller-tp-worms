#include "monitorBroadcaster.h"


BroadCaster::BroadCaster(){

}

void BroadCaster::add_queue(Queue<Mensaje>* q){
    lista.push_back(q);
}

void BroadCaster::broadcastSnap(Mensaje snap){
    for (auto& c: lista) {
        c->push(snap);
    }
}