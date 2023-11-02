#include "comando.h"


struct DetenerMovimiento:public Comando{

    uint8_t responsable_id;

    DetenerMovimiento(uint8_t responsable_id);

    void agregar_id(uint8_t id) override;

    void realizar_accion(Mapa &mapa) override;


};