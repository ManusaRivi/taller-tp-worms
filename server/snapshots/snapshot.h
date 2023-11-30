#ifndef SNAPSHOT_SERVER_H
#define SNAPSHOT_SERVER_H
#include "../worm_wrapper.h"
#include "../projectile_wrapper.h"
#include "../explosion_wrapper.h"
#include <vector>

enum tipo_snapshot{
    TIPO_HANDSHAKE = 0,
    TIPO_PARTIDA = 1,
};

class Snapshot{

    uint8_t tipo_snapshot;
    public:
    Snapshot(uint8_t tipo);
    uint8_t get_tipo_snapshot();

    virtual std::vector<WormWrapper>& get_worms() = 0;
    virtual ~Snapshot() = default;

};


#endif