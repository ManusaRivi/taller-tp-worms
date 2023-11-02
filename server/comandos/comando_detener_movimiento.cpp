#include "comando_detener_movimiento.h"


DetenerMovimiento::DetenerMovimiento(uint8_t id): responsable_id(id){

}

    void DetenerMovimiento::agregar_id(uint8_t id){

    }

    void DetenerMovimiento::realizar_accion(Mapa &mapa){
        int id;
        if (responsable_id == 0x00){
            id = 0;
        }
        else{
            id = 1;
        }
        mapa.StopWorm(id);
    }


