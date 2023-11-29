#include "cambiar_direccion_arma.h"


CambiarDireccionArma::CambiarDireccionArma(uint8_t direccion, uint32_t id_responsable):Comando(id_responsable),dir(direccion){

}

void CambiarDireccionArma::realizar_accion(Mapa& mapa){

        int direccion;

    if(dir == 0x01){
        direccion = 0;
    }
    else{
        direccion = 1;
    }

    mapa.cambiar_direccion(this->get_responsable(),direccion);
}