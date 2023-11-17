#include "comando_detener_movimiento.h"


DetenerMovimientoCliente::DetenerMovimientoCliente(uint32_t id): Comando(id){

}

    void DetenerMovimientoCliente::agregar_id(uint8_t id){

    }

    void DetenerMovimientoCliente::realizar_accion(Mapa &mapa, uint32_t id){
        printf("Se ejecuta la accion de detener el worm para el id %u \n",id);
        mapa.StopWorm(id);
    }

    uint8_t DetenerMovimientoCliente::get_comando(){
        return this->tipo_comando;
    }



