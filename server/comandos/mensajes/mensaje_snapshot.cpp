#include "mensaje_snapshot.h"

MensajeSnapshotServer::MensajeSnapshotServer(std::shared_ptr<Snapshot> snap_):MensajeServer(COMANDO::CMD_ENVIAR_SNAPSHOT),snap(snap_){
    
}


std::shared_ptr<Snapshot> MensajeSnapshotServer::get_snap(){
    return this->snap;
}