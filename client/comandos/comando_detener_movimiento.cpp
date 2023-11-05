#include "comando_detener_movimiento.h"


DetenerMovimiento::DetenerMovimiento(){

}

void DetenerMovimiento::enviar_accion(ClienteProtocolo &ptcl){
    ptcl.detener_movimiento();
}