#include "comando_detener_movimiento.h"


DetenerMovimiento::DetenerMovimiento(): responsable_id(0){

}

    void DetenerMovimiento::agregar_id(uint8_t id){

    }

    void DetenerMovimiento::realizar_accion(Mapa &mapa){
        printf("Se ejecuta la accion de detener el worm\n");
        int id;
        if (this->id_gusano == 0x00){
            id = 0;
        }
        else{
            id = 1;
        }
        mapa.StopWorm(id);
    }

    uint8_t DetenerMovimiento::get_comando(){
        return this->tipo_comando;
    }



