#include "detener_angulo.h"


DetenerAngulo::DetenerAngulo(uint32_t id):Comando(id){

}


void DetenerAngulo::realizar_accion(Mapa &mapa , uint32_t id){
    mapa.detener_angulo(id);
}