#ifndef _COMANDOMOVIMIENTO
#define _COMANDOMOVIMIENTO
#include "comando.h"


struct ComandoMovimiento:public Comando{

    uint8_t dir;
    uint8_t responsable_id;

    ComandoMovimiento(uint8_t direccion, uint8_t id);



    void agregar_id(uint8_t id);

    void realizar_accion(Mapa &mapa) override;

};

#endif