#include "comando.h"


class SaltarCliente:public ComandoCliente{

    uint8_t direccion;

    public:
    SaltarCliente(uint8_t dir);

    void enviar_accion(ClienteProtocolo &ptcl) override;

};