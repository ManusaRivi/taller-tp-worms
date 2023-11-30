#ifndef MENSAJE_HANDSHAKE_H_SERVER
#define MENSAJE_HANDSHAKE_H_SERVER

#include "mensaje.h"
#include "../../snapshots/snapshot_handshake.h"
#include <memory>


class MensajeHandshakeServer:public MensajeServer{

    std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player;
    std::shared_ptr<Snapshot> snap;


    public:
    MensajeHandshakeServer(std::shared_ptr<Snapshot> snap_,std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player_);
    std::shared_ptr<Snapshot>& get_snap();
    std::pair<uint32_t,std::vector<uint32_t>>& get_gusanos_por_player_();

};

#endif