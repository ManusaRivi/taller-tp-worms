#include "snapshot_partida.h"


SnapshotPartida::SnapshotPartida(std::vector<WormWrapper> worms_,
                                std::vector<ProjectileWrapper> proyectiles_,
                                std::vector<ExplosionWrapper> explosiones_,
                                std::vector<ProvisionWrapper> provisiones_,
                                float tiempo_actual_, uint32_t gusano_actual_,
                                uint32_t id_a_seguir_,
                                std::vector<SoundTypes> sonidos,
                                std::vector<std::pair<uint8_t,std::vector<float>>> armas_especiales_,
                                std::vector<std::pair<int,int>> municion_armas_,
                                uint16_t carga_actual_,
                                float viento_,
                                bool es_negativo_):
                Snapshot(tipo_snapshot::TIPO_PARTIDA, worms_, gusano_actual_),
                proyectiles(proyectiles_),
                explosiones(explosiones_),
                provisiones(provisiones_),
                tiempo_actual(tiempo_actual_),
                
                sonidos(sonidos),
                armas_especiales(armas_especiales_),
                municion_armas(municion_armas_),
                carga_actual(carga_actual_),
                viento(viento_),
                es_negativo(es_negativo_),
                id_a_seguir(id_a_seguir_) {}

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

std::vector<std::pair<int,int>>& SnapshotPartida::get_municion_armas(){
    return this->municion_armas;
}
uint16_t& SnapshotPartida::get_carga_actual(){
    return this->carga_actual;
}

float& SnapshotPartida::get_viento(){
    return this->viento;
}

bool& SnapshotPartida::viento_es_negativo(){
    return this->es_negativo;
}

uint32_t& SnapshotPartida::get_id_a_seguir(){
    return this->id_a_seguir;
}