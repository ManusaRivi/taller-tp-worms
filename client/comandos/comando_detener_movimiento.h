#include "comando.h"


struct DetenerMovimiento:public Comando{

    DetenerMovimiento();

    void enviar_accion(ClienteProtocolo &ptcl) override;

};