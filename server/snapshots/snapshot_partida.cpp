#include "snapshot_partida.h"


SnapshotPartida::SnapshotPartida(std::vector<WormWrapper> worms_,
                                std::vector<ProjectileWrapper> proyectiles_,
                                std::vector<ExplosionWrapper> explosiones_,
                                std::vector<ProvisionWrapper> provisiones_,
                                float tiempo_actual_, uint32_t gusano_actual_,
                                std::vector<SoundTypes> sonidos,
                                std::vector<std::pair<uint8_t,std::vector<float>>> armas_especiales_) :
                Snapshot(tipo_snapshot::TIPO_PARTIDA, worms_, gusano_actual_),
                proyectiles(proyectiles_),
                explosiones(explosiones_),
                provisiones(provisiones_),
                tiempo_actual(tiempo_actual_),
                sonidos(sonidos),
                armas_especiales(armas_especiales_) {}

float SnapshotPartida::get_tiempo_actual(){
    return this->tiempo_actual;
}

uint32_t SnapshotPartida::get_gusano_actual(){
    return this->gusano_actual;
}

std::vector<ProjectileWrapper>& SnapshotPartida::get_proyectiles(){
    return this->proyectiles;
}

std::vector<ExplosionWrapper>& SnapshotPartida::get_explosiones(){
    return this->explosiones;
}

std::vector<ProvisionWrapper>& SnapshotPartida::get_provisiones(){
    return this->provisiones;
}

std::vector<SoundTypes>& SnapshotPartida::get_sonidos() {
    return this->sonidos;
}

std::vector<std::pair<uint8_t,std::vector<float>>>& SnapshotPartida::get_armas_especiales(){
    return this->armas_especiales;
}
