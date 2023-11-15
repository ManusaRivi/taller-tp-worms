#include "snapshot.h"

Snapshot::Snapshot() {}


void Snapshot::add_worm(std::shared_ptr<Worm> worm, int& id) {
    worms.emplace(id, worm);
}

void Snapshot::apply_to_world(World& world) {
    for (const auto& pair: worms) {
        world.update_worm(pair.first, std::move(pair.second));
    }
}

void Snapshot::agregar_turno_actual(uint32_t turno){
    this->id_turno_actual = turno;
}

void Snapshot::imprimir_posiciones(){
    for (auto &worm : worms){
        printf("La posicion x es = %f\n",worm->get_x());
    }
}