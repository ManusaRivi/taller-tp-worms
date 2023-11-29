#include "disparar.h"



Disparar::Disparar(uint32_t id):Comando(id){

}


void Disparar::realizar_accion(Mapa& mapa){
    mapa.usar_arma(this->get_responsable());
}