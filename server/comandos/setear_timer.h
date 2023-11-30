#include "comando.h"


class SetearTimer:public Comando{

    uint32_t time;
    public:
    
    SetearTimer(uint32_t time, uint32_t id_responsable);

    void realizar_accion(Mapa& mapa) override;


};