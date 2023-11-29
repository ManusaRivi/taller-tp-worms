#include "comando.h"


class SetearTimerCliente : public ComandoCliente{

    uint32_t time;

    public:
    SetearTimerCliente(uint32_t time_);

    void enviar_accion(ClienteProtocolo &ptcl) override;

};