#include "snapshot_partida.h"


SnapshotPartida::SnapshotPartida(std::vector<WormWrapper> worms_, 
                std::vector<ProjectileWrapper> proyectiles_, 
                float tiempo_actual_, uint32_t gusano_actual_):Snapshot(tipo_snapshot::TIPO_PARTIDA),worms(worms_),
                                                            proyectiles(proyectiles_),
                                                            tiempo_actual(tiempo_actual_),
                                                            gusano_actual(gusano_actual_){

                                                            }


    std::vector<WormWrapper> SnapshotPartida::get_worms(){
        return this->worms;
    }
    std::vector<ProjectileWrapper> SnapshotPartida::get_proyectiles(){
        return this->proyectiles;
    }
    float SnapshotPartida::get_tiempo_actual(){
        return this->tiempo_actual;
    }
    uint32_t SnapshotPartida::get_gusano_actual(){
        return this->gusano_actual;
    }