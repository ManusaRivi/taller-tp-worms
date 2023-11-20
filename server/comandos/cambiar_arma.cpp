#include "cambiar_arma.h"


CambiarArma::CambiarArma(uint8_t tipo, uint32_t id):Comando(id),tipo_arma(tipo){

}

void CambiarArma::realizar_accion(Mapa* mapa){
    mapa->cambiar_arma(this->get_responsable(),tipo_arma);
}