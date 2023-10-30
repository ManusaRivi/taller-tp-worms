#include "snapshot.h"

Snapshot::Snapshot(std::vector<std::vector<int>> vigas): vigas(vigas) {}


void Snapshot::add_worm(Worm worm) {
    worms.push_back(worm);
}

std::vector<Worm> Snapshot::get_worms(){
    return worms;
}