#include "comando.h"


class CambiarAngulo:public Comando{

    uint8_t direccion;

    public:
    
    CambiarAngulo(uint8_t dir, uint32_t id_responsable);

    void realizar_accion(Mapa &mapa , uint32_t id) override;


};