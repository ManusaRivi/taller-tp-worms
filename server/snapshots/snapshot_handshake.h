#ifndef SNAPSHOT_HANDSHAKE_H
#define SNAPSHOT_HANDSHAKE_H

#include "snapshot.h"



class SnapshotHandshake : public Snapshot{
    std::vector<std::vector<float>> vigas;
    uint8_t background_type;
    public:
    SnapshotHandshake(std::vector<WormWrapper> worms_, std::vector<std::vector<float>> vigas_,uint32_t gusano_atual_, uint8_t background);
    std::vector<std::vector<float>>& get_vigas();
    uint32_t get_gusano_actual();
    uint8_t get_background();
};

#endif
