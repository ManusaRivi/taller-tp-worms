#include "snapshot.h"

SnapshotCliente::SnapshotCliente(std::vector<std::vector<float>> vigas): vigas(vigas) {}


void SnapshotCliente::add_worm(std::shared_ptr<Worm> worm) {
    worms.push_back(worm);
}

void SnapshotCliente::present(int& it,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale){
    

    //Esto hay que encontrar la manera de cambiarlo (lo la run_phase)
    for (auto& worm : worms) {
        worm->present(it, renderer, texture_manager, x_scale, y_scale);
    }

    renderer.Present();
}

void SnapshotCliente::agregar_turno_actual(uint32_t turno){
    this->id_turno_actual = turno;
}

void SnapshotCliente::imprimir_posiciones(){
    for (auto &worm : worms){
        printf("La posicion x es = %f\n",worm->get_x());
    }
}

void SnapshotCliente::agregar_vigas(std::vector<std::vector<float>> vigas){
    this->vigas = vigas;
}