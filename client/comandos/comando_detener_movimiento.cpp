#include "comando_detener_movimiento.h"


DetenerMovimiento::DetenerMovimiento(){

}

void DetenerMovimiento::enviar_accion(Protocolo &ptcl){
    ptcl.detener_movimiento();
}