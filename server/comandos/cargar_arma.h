#include "comando.h"


class CargarArma:public Comando{


    public:
    CargarArma(uint32_t id);


    void realizar_accion(Mapa* mapa , uint32_t id) override;


};