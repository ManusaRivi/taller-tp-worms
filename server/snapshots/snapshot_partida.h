#ifndef SNAPSHOT_PARTIDA_H
#define SNAPSHOT_PARTIDA_H
#include "snapshot.h"


class SnapshotPartida:public Snapshot{

    std::vector<WormWrapper> worms;
    std::vector<ProjectileWrapper> proyectiles;
    std::vector<ExplosionWrapper> explosiones;
    std::vector<ProvisionWrapper> provisiones;
    float tiempo_actual;
    std::vector<ExplosionWrapper> cementerio_explosiones;
    std::vector<ProjectileWrapper> cementerio_proyectiles;
    std::vector<SoundTypes> sonidos;
    std::vector<std::pair<uint8_t,std::vector<float>>> armas_especiales;
    std::vector<std::pair<int,int>> municion_armas;
    uint16_t carga_actual;
    float viento;
    bool es_negativo;
    uint32_t id_a_seguir;

    public:
    SnapshotPartida(std::vector<WormWrapper> worms_, 
                    std::vector<ProjectileWrapper> proyectiles_,
                    std::vector<ExplosionWrapper> explosiones_,
                    std::vector<ProvisionWrapper> provisiones_, 
                    float tiempo_actual_, uint32_t gusano_actual_,
                    uint32_t id_a_seguir,
                    std::vector<SoundTypes> sonidos,
                    std::vector<std::pair<uint8_t,std::vector<float>>> armas_especiales_,
                    std::vector<std::pair<int,int>> municion_armas,
                    uint16_t carga_actual,
                    float viento,
                    bool es_negativo
                    );

    float get_tiempo_actual(); 
    uint32_t get_gusano_actual();
    std::vector<ProjectileWrapper>& get_proyectiles();
    std::vector<ExplosionWrapper>& get_explosiones();
    std::vector<ProvisionWrapper>& get_provisiones();
    std::vector<SoundTypes>& get_sonidos();
    std::vector<std::pair<uint8_t,std::vector<float>>>& get_armas_especiales();
    std::vector<std::pair<int,int>>& get_municion_armas();
    uint16_t& get_carga_actual();
    float& get_viento();
    bool& viento_es_negativo();
    uint32_t& get_id_a_seguir();
};
#endif
