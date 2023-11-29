#include "detener_angulo.h"


DetenerAngulo::DetenerAngulo(uint32_t id):Comando(id){

}


void DetenerAngulo::realizar_accion(Mapa& mapa){
    mapa.detener_angulo(this->get_responsable());
}