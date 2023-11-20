#include "comando.h"


class CambiarDireccionArmaCliente:public ComandoCliente{

    uint8_t dir;
    public:

    CambiarDireccionArmaCliente(uint8_t dir);
    void enviar_accion(ClienteProtocolo &ptcl) override;

};