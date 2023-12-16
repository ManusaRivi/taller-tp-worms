#include "monitorBroadcaster.h"


BroadCaster::BroadCaster(){

}

void BroadCaster::add_queue(Queue<std::shared_ptr<MensajeServer>>* q){
    std::lock_guard<std::mutex> lock(lck);
    lista.push_back(q);
}

void BroadCaster::broadcastSnap(std::shared_ptr<MensajeServer> snap){
    std::lock_guard<std::mutex> lock(lck);
    for (auto& c: lista) {
        c->push(snap);
    }
}

uint32_t BroadCaster::cantidad_jugadores(){
    std::lock_guard<std::mutex> lock(lck);
    return this->lista.size();
}

void BroadCaster::informar_primer_snapshot(std::map<uint32_t,std::vector<uint32_t>> gusanos_por_player,
                                        std::shared_ptr<SnapshotHandshake> snap){
    std::lock_guard<std::mutex> lock(lck);
    uint32_t i =0;
    for (auto& c: lista) {
        uint32_t id_player = i;
        std::vector<uint32_t> id_gusanos = gusanos_por_player[i];
        std::pair<uint32_t,std::vector<uint32_t>> par({id_player,id_gusanos});
        std::shared_ptr<MensajeServer> msg = mensajes.handshake(snap,par);
        c->push(msg);
        i++;
    }
}

void BroadCaster::remover_player(Queue<std::shared_ptr<MensajeServer>>* q){
    std::lock_guard<std::mutex> lock(lck);
    lista.remove(q);
}
