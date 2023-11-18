#include "detener_movimiento.h"


DetenerMovimiento::DetenerMovimiento(uint32_t id): Comando(id){

}


    void DetenerMovimiento::realizar_accion(Mapa* mapa, uint32_t id){
        printf("Se ejecuta la accion de detener el worm para el id %u \n",id);
        mapa->StopWorm(id);
    }




