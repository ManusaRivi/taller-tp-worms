#ifndef SNAPSHOT_PARTIDA_H
#define SNAPSHOT_PARTIDA_H
#include "snapshot.h"


class SnapshotPartida:public Snapshot{

    std::vector<WormWrapper> worms;
    std::vector<ProjectileWrapper> proyectiles;
    float tiempo_actual; 
    uint32_t gusano_actual;


    public:
    SnapshotPartida(std::vector<WormWrapper> worms_, 
                std::vector<ProjectileWrapper> proyectiles_, 
                float tiempo_actual_, uint32_t gusano_actual_);

    std::vector<WormWrapper> get_worms() override;
    std::vector<ProjectileWrapper> get_proyectiles();
    float get_tiempo_actual(); 
    uint32_t get_gusano_actual();


};

#endif
