#include "comando_setear_timer.h"


SetearTimerCliente::SetearTimerCliente(uint32_t time_):time(time_){

}


void SetearTimerCliente::enviar_accion(ClienteProtocolo &ptcl){
    ptcl.enviar_timer(time);
}
