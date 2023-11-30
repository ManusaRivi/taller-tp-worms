#include "snapshot_partida.h"


SnapshotPartida::SnapshotPartida(std::vector<WormWrapper> worms_, 
                                std::vector<ProjectileWrapper> proyectiles_,
                                std::vector<ExplosionWrapper> explosiones_, 
                                float tiempo_actual_, uint32_t gusano_actual_,
                                std::vector<ExplosionWrapper> cementerio_explosiones_,
                                std::vector<ProjectileWrapper> cementerio_proyectiles_,
                                std::vector<SoundTypes> sonidos) :
                Snapshot(tipo_snapshot::TIPO_PARTIDA), worms(worms_),
                proyectiles(proyectiles_),
                explosiones(explosiones_),
                tiempo_actual(tiempo_actual_),
                gusano_actual(gusano_actual_),
                cementerio_explosiones(cementerio_explosiones_),
                cementerio_proyectiles(cementerio_proyectiles_),
                sonidos(sonidos) {}


std::vector<WormWrapper> SnapshotPartida::get_worms(){
    return this->worms;
}

std::vector<ProjectileWrapper> SnapshotPartida::get_proyectiles(){
    return this->proyectiles;
}

std::vector<ExplosionWrapper> SnapshotPartida::get_explosiones(){
    return this->explosiones;
}

float SnapshotPartida::get_tiempo_actual(){
    return this->tiempo_actual;
}

uint32_t SnapshotPartida::get_gusano_actual(){
    return this->gusano_actual;
}

std::vector<ExplosionWrapper> SnapshotPartida::get_cementerio_explosiones(){
    return this->cementerio_explosiones;
}

std::vector<ProjectileWrapper> SnapshotPartida::get_cementerio_proyectiles(){
    return this->cementerio_proyectiles;
}

std::vector<SoundTypes> SnapshotPartida::get_sonidos() {
    return this->sonidos;
}
