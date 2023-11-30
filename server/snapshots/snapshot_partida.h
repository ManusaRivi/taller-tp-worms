#ifndef SNAPSHOT_PARTIDA_H
#define SNAPSHOT_PARTIDA_H
#include "snapshot.h"


class SnapshotPartida:public Snapshot{

    std::vector<WormWrapper> worms;
    std::vector<ProjectileWrapper> proyectiles;
    std::vector<ExplosionWrapper> explosiones;
    float tiempo_actual; 
    uint32_t gusano_actual;
    std::vector<ExplosionWrapper> cementerio_explosiones;
    std::vector<ProjectileWrapper> cementerio_proyectiles;


    public:
    SnapshotPartida(std::vector<WormWrapper> worms_, 
                std::vector<ProjectileWrapper> proyectiles_,
                std::vector<ExplosionWrapper> explosiones_, 
                float tiempo_actual_, uint32_t gusano_actual_,
                std::vector<ExplosionWrapper> cementerio_explosiones_,
                std::vector<ProjectileWrapper> cementerio_proyectiles_
                );

    std::vector<WormWrapper>& get_worms() override;
    std::vector<ProjectileWrapper>& get_proyectiles();
    std::vector<ExplosionWrapper>& get_explosiones();
    float& get_tiempo_actual(); 
    uint32_t& get_gusano_actual();
    std::vector<ExplosionWrapper>& get_cementerio_explosiones();
    std::vector<ProjectileWrapper>& get_cementerio_proyectiles();


};

#endif
