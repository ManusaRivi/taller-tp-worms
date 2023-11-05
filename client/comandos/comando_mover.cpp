#include "comando_mover.h"


ComandoMover::ComandoMover(uint8_t direccion):dir(direccion){

}

void ComandoMover::enviar_accion(ClienteProtocolo &ptcl){
    ptcl.enviar_movimiento(this->dir);
}