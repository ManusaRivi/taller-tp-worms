#include "detener_movimiento.h"


DetenerMovimiento::DetenerMovimiento(uint32_t id): Comando(id){

}


    void DetenerMovimiento::realizar_accion(Mapa* mapa){
        printf("Se ejecuta la accion de detener el worm para el id %u \n",this->get_responsable());
        mapa->StopWorm(this->get_responsable());
    }




