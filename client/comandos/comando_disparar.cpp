#include "comando_disparar.h"


DispararArmaCliente::DispararArmaCliente(){

}


void DispararArmaCliente::enviar_accion(ClienteProtocolo& ptcl){
    ptcl.disparar_arma();
}