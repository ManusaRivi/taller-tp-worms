#include "comando_detener_movimiento.h"


DetenerMovimientoCliente::DetenerMovimientoCliente(uint32_t id): responsable_id(id){

}

    void DetenerMovimientoCliente::agregar_id(uint8_t id){

    }

    void DetenerMovimientoCliente::realizar_accion(Mapa &mapa, uint32_t id){
        printf("Se ejecuta la accion de detener el worm para el id %u \n",id);
        int idx;
        if (id == 1){
            idx = 0;
        }
        else{
            idx = 1;
        }
        mapa.StopWorm(idx);
    }

    uint8_t DetenerMovimientoCliente::get_comando(){
        return this->tipo_comando;
    }



