#include "comando.h"


class ActivarCheatCliente:public ComandoCliente{

    uint8_t tipo_de_cheat;
    
    public:
    ActivarCheatCliente(uint8_t tipo_de_cheat);
    void enviar_accion(ClienteProtocolo& ptcl) override;


};