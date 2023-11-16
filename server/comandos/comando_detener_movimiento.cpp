#include "comando_detener_movimiento.h"


DetenerMovimiento::DetenerMovimiento(): responsable_id(0){

}

    void DetenerMovimiento::agregar_id(uint8_t id){

    }

    void DetenerMovimiento::realizar_accion(Mapa* mapa, uint32_t id){
        printf("Se ejecuta la accion de detener el worm\n");
        int idx;
        if (id == 1){
            idx = 0;
        }
        else{
            idx = 1;
        }
        mapa->StopWorm(idx);
    }

    uint8_t DetenerMovimiento::get_comando(){
        return this->tipo_comando;
    }



