#include "snapshot_handshake.h"

SnapshotHandshake::SnapshotHandshake(std::vector<WormWrapper> worms_, 
                                    std::vector<std::vector<float>> vigas_,
                                    uint32_t gusano_actual_):
                    Snapshot(tipo_snapshot::TIPO_HANDSHAKE),
                    worms(worms_),
                    vigas(vigas_),
                    gusano_actual(gusano_actual_) {}


std::vector<WormWrapper> SnapshotHandshake::get_worms(){
    return this->worms;
}

std::vector<std::vector<float>> SnapshotHandshake::get_vigas(){
    return this->vigas;
}

uint32_t SnapshotHandshake::get_gusano_actual(){
    return this->gusano_actual;
}
