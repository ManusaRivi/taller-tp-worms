#include "comando.h"


class ActivarCheat:public Comando{

    uint8_t tipo_de_cheat;

    public:
    
    ActivarCheat(uint8_t tipo_de_cheat, uint32_t id_responsable);

    void realizar_accion(Mapa& mapa) override;


};