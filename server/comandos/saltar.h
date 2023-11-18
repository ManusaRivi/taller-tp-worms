#include "comando.h"


class Saltar:public Comando{

    uint8_t direc_salto;


    public:
    Saltar(uint8_t direccion,uint32_t id_responsable);


    void realizar_accion(Mapa* mapa , uint32_t id) override;

};