#ifndef SNAPSHOT_SERVER_H
#define SNAPSHOT_SERVER_H
#include "../worm_wrapper.h"
#include "../projectile_wrapper.h"
#include "../explosion_wrapper.h"
#include "../../common/sound_types.h"
#include <vector>

enum tipo_snapshot{
    TIPO_HANDSHAKE = 0,
    TIPO_PARTIDA = 1,
};

class Snapshot{
    protected:
    std::vector<WormWrapper> worms;
    uint8_t tipo_snapshot;
    uint32_t gusano_actual;
    public:
    Snapshot(uint8_t tipo, std::vector<WormWrapper> worms, uint32_t gusano_actual) : tipo_snapshot(tipo), worms(worms), gusano_actual(gusano_actual) {}
    uint8_t get_tipo_snapshot();

    virtual std::vector<WormWrapper>& get_worms() { return this->worms; }
    virtual ~Snapshot() = default;

};


#endif