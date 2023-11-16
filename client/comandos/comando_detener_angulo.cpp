#include "comando_detener_angulo.h"


DetenerAnguloCliente::DetenerAnguloCliente(){

}

void DetenerAnguloCliente::enviar_accion(ClienteProtocolo& ptcl){
    ptcl.detener_cambio_angulo();
}