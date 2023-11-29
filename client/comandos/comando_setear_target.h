#include "comando.h"


class SetearTargetCliente : public ComandoCliente{

    float x;
    float y;

    public:
    SetearTargetCliente(float x, float y);

    void enviar_accion(ClienteProtocolo &ptcl) override;

};