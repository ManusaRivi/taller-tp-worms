#include "comando.h"


class CambiarArmaCliente:public ComandoCliente{


    uint8_t id_arma;

    public:
    CambiarArmaCliente(uint8_t id);
    void enviar_accion(ClienteProtocolo &ptcl) override;
};