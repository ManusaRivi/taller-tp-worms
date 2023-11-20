#include "mensaje_snapshot.h"


MensajeSnapshot::MensajeSnapshot(std::shared_ptr<SnapshotCliente> snap_):MensajeCliente(COMANDO::CMD_ENVIAR_SNAPSHOT),snap(snap_){

}

std::shared_ptr<SnapshotCliente> MensajeSnapshot::get_snap(){
    return this->snap;
}