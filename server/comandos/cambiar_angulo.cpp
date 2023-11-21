#include "cambiar_angulo.h"

#define ARRIBA 0x00
#define ABAJO 0x01


CambiarAngulo::CambiarAngulo(uint8_t dir, uint32_t id_responsable):Comando(id_responsable),direccion(dir){

}


void CambiarAngulo::realizar_accion(Mapa* mapa){
    if(direccion == ARRIBA){
        mapa->apuntar_para(this->get_responsable(),1);
    }
    else{
        mapa->apuntar_para(this->get_responsable(),0);
    }
}