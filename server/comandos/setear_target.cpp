#include "setear_target.h"


SetearTarget::SetearTarget(float x_, float y_, uint32_t id_responsable):Comando(id_responsable),x(x_),y(y_){
    std::cout << "Recibi target x=" << x << " y=" << y << "\n";
}



void SetearTarget::realizar_accion(Mapa& mapa){
    mapa.set_target(this->get_responsable(),x,y);
}