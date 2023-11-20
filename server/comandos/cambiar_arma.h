#include "comando.h"


class CambiarArma:public Comando{

    uint8_t tipo_arma;
    
    public:
    CambiarArma(uint8_t tipo,uint32_t id_responsable);

    void realizar_accion(Mapa* mapa) override;

};