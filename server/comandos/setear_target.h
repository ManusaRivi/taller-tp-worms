#include "comando.h"


class SetearTarget:public Comando{

    float x;
    float y;

    public:
    
    SetearTarget(float x, float y, uint32_t id_responsable);

    void realizar_accion(Mapa& mapa) override;


};