#include "comando_setear_target.h"


SetearTargetCliente::SetearTargetCliente(float x_, float y_):x(x_),y(y_){

}



void SetearTargetCliente::enviar_accion(ClienteProtocolo& ptcl){
    ptcl.enviar_target(x,y);
}