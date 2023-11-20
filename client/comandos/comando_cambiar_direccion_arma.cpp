#include "comando_cambiar_direccion_arma.h"


CambiarDireccionArmaCliente::CambiarDireccionArmaCliente(uint8_t dir_):dir(dir_){

}


void CambiarDireccionArmaCliente::enviar_accion(ClienteProtocolo &ptcl){
    ptcl.enviar_cambio_direccion_apuntado(dir);
}
