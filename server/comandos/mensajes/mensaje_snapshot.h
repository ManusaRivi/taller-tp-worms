#ifndef MENSAJE_SNAPSHOT_SERVER_H
#define MENSAJE_SNAPSHOT_SERVER_H


#include "mensaje.h"
#include "../../snapshots/snapshot.h"
#include <memory>


class MensajeSnapshotServer:public MensajeServer{

    std::shared_ptr<Snapshot> snap;

    public:
    MensajeSnapshotServer(std::shared_ptr<Snapshot> snap_);

    std::shared_ptr<Snapshot>& get_snap();


};

#endif