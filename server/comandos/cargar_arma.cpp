#include "cargar_arma.h"


CargarArma::CargarArma(uint32_t id):Comando(id){

}


void CargarArma::realizar_accion(Mapa* mapa_gusano){
    mapa_gusano->cargar_arma(this->get_responsable());
}