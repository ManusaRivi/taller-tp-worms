#include "comando.h"



class DetenerAnguloCliente:public ComandoCliente{


    public:
    DetenerAnguloCliente();
    void enviar_accion(ClienteProtocolo& ptcl) override;
};