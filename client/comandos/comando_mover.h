#include "comando.h"

class ComandoMoverCliente: public ComandoCliente{

    uint8_t dir;
    public:
    ComandoMoverCliente(uint8_t dir);
    void enviar_accion(ClienteProtocolo &ptcl) override;

};