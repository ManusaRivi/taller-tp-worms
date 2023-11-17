#include "monitorBroadcaster.h"


BroadCaster::BroadCaster(){

}

void BroadCaster::add_queue(Queue<Mensaje>* q){
    std::lock_guard<std::mutex> lock(lck);
    lista.push_back(q);
}

void BroadCaster::broadcastSnap(Mensaje snap){
    std::lock_guard<std::mutex> lock(lck);
    for (auto& c: lista) {
        c->push(snap);
    }
}

uint16_t BroadCaster::cantidad_jugadores(){
    std::lock_guard<std::mutex> lock(lck);
    return this->lista.size();
}

void BroadCaster::informar_primer_snapshot(std::map<uint32_t,std::vector<uint32_t>> gusanos_por_player,
                                        std::vector<std::vector<float>> vigas){
    std::lock_guard<std::mutex> lock(lck);
    uint16_t i =0;
    for (auto& c: lista) {
        printf("Se envia el id : %u \n", i);
        uint32_t id_player = i;
        std::vector<uint32_t> id_gusanos = gusanos_por_player[i];
        std::pair<uint32_t,std::vector<uint32_t>> par({id_player,id_gusanos});
        printf("Se envia un vector de tamanio %lu \n", id_gusanos.size());
        Mensaje msg(par,vigas);
        c->push(msg);
        i++;
    }
}

void BroadCaster::remover_player(Queue<Mensaje>* q){
    std::lock_guard<std::mutex> lock(lck);
    lista.remove(q);
}