#include "activar_cheat.h"



ActivarCheat::ActivarCheat(uint8_t tipo_de_cheat_, uint32_t id_responsable):Comando(id_responsable),tipo_de_cheat(tipo_de_cheat_){

}


void ActivarCheat::realizar_accion(Mapa& mapa){
    if(tipo_de_cheat == Cheats::SETEAR_VIDA_A_1) {
        mapa.reducir_vida();
    } else if (tipo_de_cheat == Cheats::SUPER_VELOCIDAD) {
        mapa.super_velocidad();
    } else if (tipo_de_cheat == Cheats::SUPER_SALTO) {
        mapa.super_salto();
    }
}