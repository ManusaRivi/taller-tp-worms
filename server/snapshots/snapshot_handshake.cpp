#include "snapshot_handshake.h"

SnapshotHandshake::SnapshotHandshake(std::vector<WormWrapper> worms_, 
                                    std::vector<std::vector<float>> vigas_,
                                    uint32_t gusano_actual_):
                    Snapshot(tipo_snapshot::TIPO_HANDSHAKE, worms_, gusano_actual_),
                    vigas(vigas_) {}

std::vector<std::vector<float>>& SnapshotHandshake::get_vigas(){
    return this->vigas;
}

uint32_t SnapshotHandshake::get_gusano_actual(){
    return this->gusano_actual;
}
