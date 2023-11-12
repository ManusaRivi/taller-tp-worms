#include "snapshot.h"

Snapshot::Snapshot(std::vector<std::vector<int>> vigas): vigas(vigas) {}


void Snapshot::add_worm(Worm worm) {
    worms.push_back(worm);
}

void Snapshot::present(int& it,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale){
    

    //Esto hay que encontrar la manera de cambiarlo (lo la run_phase)
    for (auto& worm : worms) {
        worm.present(it, renderer, texture_manager, x_scale, y_scale);
    }

    renderer.Present();
}

void Snapshot::agregar_turno_actual(uint32_t turno){
    this->id_turno_actual = turno;
}