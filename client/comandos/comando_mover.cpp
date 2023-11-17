#include "comando_mover.h"


ComandoMoverCliente::ComandoMoverCliente(uint8_t direccion):dir(direccion){

}

void ComandoMoverCliente::enviar_accion(ClienteProtocolo &ptcl){
    ptcl.enviar_movimiento(this->dir);
}