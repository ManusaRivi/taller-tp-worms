#include "snapshot.h"

Snapshot::Snapshot(std::vector<std::vector<int>> vigas): vigas(vigas) {}


void Snapshot::add_worm(Worm worm) {
    worms.push_back(worm);
}

void Snapshot::present(int run_phase,
                        Renderer& renderer,
                        Texture& wwalk,
                        int& vcenter){
    

    //Esto hay que encontrar la manera de cambiarlo (lo la run_phase)
    for (auto& worm : worms) {
        worm.present(run_phase, renderer, wwalk, vcenter);
    }

    renderer.Present();
}