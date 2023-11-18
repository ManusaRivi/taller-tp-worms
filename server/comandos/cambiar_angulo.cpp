#include "cambiar_angulo.h"

#define ARRIBA 0x00
#define ABAJO 0x01


CambiarAngulo::CambiarAngulo(uint8_t dir, uint32_t id):Comando(id),direccion(dir){

}


void CambiarAngulo::realizar_accion(Mapa& mapa, uint32_t id){
    if(direccion == ARRIBA){
        mapa.apuntar_para(id,1);
    }
    else{
        mapa.apuntar_para(id,0);
    }
}