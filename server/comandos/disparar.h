#include "comando.h"


class Disparar:public Comando{


    public:
    Disparar(uint32_t id_responsable);

    void realizar_accion(Mapa &mapa , uint32_t id) override;


};