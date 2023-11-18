#include "comando_saltar.h"


SaltarCliente::SaltarCliente(uint8_t dir):direccion(dir){

}


void SaltarCliente::enviar_accion(ClienteProtocolo& ptcl){
    ptcl.enviar_salto(direccion);
}