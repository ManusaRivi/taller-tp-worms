#include "comando_cargar_arma.h"

CargarArmaCliente::CargarArmaCliente(){

}

void CargarArmaCliente::enviar_accion(ClienteProtocolo& ptcl){
    ptcl.cargar_arma();
}