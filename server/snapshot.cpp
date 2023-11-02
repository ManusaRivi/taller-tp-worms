#include "snapshot.h"

Snapshot::Snapshot(std::vector<std::vector<int>> vigas): vigas(vigas) {}


void Snapshot::add_worm(WormWrapper worm) {
    worms.push_back(worm);
}

std::vector<WormWrapper> Snapshot::get_worms(){
    return worms;
}
