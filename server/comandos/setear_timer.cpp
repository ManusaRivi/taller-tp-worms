#include "setear_timer.h"


SetearTimer::SetearTimer(uint32_t time_, uint32_t id_responsable):Comando(id_responsable),time(time_){

}



void SetearTimer::realizar_accion(Mapa& mapa){
    mapa.set_grenade_time(this->get_responsable(),time);
}