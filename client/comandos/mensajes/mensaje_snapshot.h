#include "mensaje_cliente.h"
#include "../../game/comunicacion/snapshot.h"


class MensajeSnapshot:public MensajeCliente{

    std::shared_ptr<SnapshotCliente> snap;

    public:
    MensajeSnapshot(std::shared_ptr<SnapshotCliente> snap_);
    std::shared_ptr<SnapshotCliente> get_snap();


};