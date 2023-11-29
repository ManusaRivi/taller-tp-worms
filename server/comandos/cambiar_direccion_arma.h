#include "comando.h"


class CambiarDireccionArma:public Comando{

    uint8_t dir;

    public:
    CambiarDireccionArma(uint8_t dir, uint32_t id_responsable);

    void realizar_accion(Mapa& mapa) override;

};