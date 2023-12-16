#include "comando_activar_cheat.h"

ActivarCheatCliente::ActivarCheatCliente(uint8_t dir):tipo_de_cheat(dir){

}


void ActivarCheatCliente::enviar_accion(ClienteProtocolo& ptcl){
    ptcl.enviar_cheat(this->tipo_de_cheat);
}
