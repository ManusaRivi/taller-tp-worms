#include "comando.h"


class CargarArmaCliente:public ComandoCliente{

    public:
    CargarArmaCliente();
    void enviar_accion(ClienteProtocolo &ptcl) override;

};