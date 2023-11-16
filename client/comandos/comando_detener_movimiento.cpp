#include "comando_detener_movimiento.h"


DetenerMovimientoCliente::DetenerMovimientoCliente(){

}

void DetenerMovimientoCliente::enviar_accion(ClienteProtocolo &ptcl){
    ptcl.detener_movimiento();
}