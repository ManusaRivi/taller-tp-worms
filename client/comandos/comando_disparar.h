#include "comando.h"


class DispararArmaCliente:public ComandoCliente{


    public:
    DispararArmaCliente();
    void enviar_accion(ClienteProtocolo &ptcl) override;
};