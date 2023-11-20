#include "saltar.h"


Saltar::Saltar(uint8_t dir,uint32_t id):Comando(id),direc_salto(dir){

}


void Saltar::realizar_accion(Mapa* mapa){

    if (direc_salto == 0x01) {
        mapa->JumpWormForward(this->get_responsable());
    } else {
        mapa->JumpWormBackward(this->get_responsable());
    }
}