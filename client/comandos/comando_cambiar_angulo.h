#include "comando.h"


class CambiarAnguloCliente:public ComandoCliente{

    uint8_t direccion;
    
    public:
    CambiarAnguloCliente(uint8_t direccion);
    void enviar_accion(ClienteProtocolo& ptcl) override;


};