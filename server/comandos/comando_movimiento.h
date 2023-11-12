#ifndef _COMANDOMOVIMIENTO
#define _COMANDOMOVIMIENTO
#include "comando.h"


class ComandoMovimiento:public Comando{

    uint8_t dir;
    uint8_t responsable_id;

    public:
    ComandoMovimiento(uint8_t direccion, uint8_t id);



    void agregar_id(uint8_t id);

    void realizar_accion(Mapa &mapa, uint32_t id) override;

    uint8_t get_comando() override;

};

#endif