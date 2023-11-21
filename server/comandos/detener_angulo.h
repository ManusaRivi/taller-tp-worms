#include "comando.h"


class DetenerAngulo:public Comando{


    public:
    DetenerAngulo(uint32_t id_responsable);

    void realizar_accion(Mapa* mapa) override;


};