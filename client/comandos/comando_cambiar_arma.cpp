#include "comando_cambiar_arma.h"

CambiarArmaCliente::CambiarArmaCliente(uint8_t id):id_arma(id){

}

void CambiarArmaCliente::enviar_accion(ClienteProtocolo& ptcl){
    ptcl.enviar_cambio_de_arma(id_arma);
}