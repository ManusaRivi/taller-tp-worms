#include "snapshot.h"

Snapshot::Snapshot(std::vector<std::vector<int>> vigas): vigas(vigas),snapshot_de_la_partida(true) {}

Snapshot::Snapshot(std::map<uint32_t,std::string> lista):snapshot_de_la_partida(false){

}


void Snapshot::add_worm(WormWrapper worm) {
    worms.push_back(worm);
}

std::vector<WormWrapper> Snapshot::get_worms(){
    return worms;
}

bool Snapshot::snap_partida(){
    return snapshot_de_la_partida;
}


