#ifndef DETENER_MOVIMIENTO_CLIENTE
#define DETENER_MOVIMIENTO_CLIENTE
#include "comando.h"


class DetenerMovimientoCliente:public ComandoCliente{

    public:
    DetenerMovimientoCliente();
    void enviar_accion(ClienteProtocolo &ptcl) override;

};

#endif
