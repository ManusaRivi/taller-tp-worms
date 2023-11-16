#include "comando_cambiar_angulo.h"

CambiarAnguloCliente::CambiarAnguloCliente(uint8_t dir):direccion(dir){

}


void CambiarAnguloCliente::enviar_accion(ClienteProtocolo& ptcl){
    ptcl.cambio_angulo(direccion);
}
