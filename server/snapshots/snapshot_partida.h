#ifndef SNAPSHOT_PARTIDA_H
#define SNAPSHOT_PARTIDA_H
#include "snapshot.h"


class SnapshotPartida:public Snapshot{

    std::vector<WormWrapper> worms;
    std::vector<ProjectileWrapper> proyectiles;
    std::vector<ExplosionWrapper> explosiones;
    float tiempo_actual;
    std::vector<ExplosionWrapper> cementerio_explosiones;
    std::vector<ProjectileWrapper> cementerio_proyectiles;
    std::vector<SoundTypes> sonidos;

    public:
    SnapshotPartida(std::vector<WormWrapper> worms_, 
                    std::vector<ProjectileWrapper> proyectiles_,
                    std::vector<ExplosionWrapper> explosiones_, 
                    float tiempo_actual_, uint32_t gusano_actual_,
                    std::vector<SoundTypes> sonidos
                    );

    float get_tiempo_actual(); 
    uint32_t get_gusano_actual();
    std::vector<ProjectileWrapper>& get_proyectiles();
    std::vector<ExplosionWrapper>& get_explosiones();
    std::vector<SoundTypes>& get_sonidos();
};

#endif
