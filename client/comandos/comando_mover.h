#include "comando.h"

struct ComandoMover: public Comando{

    uint8_t dir;

    ComandoMover(uint8_t dir);

    void enviar_accion(ClienteProtocolo &ptcl) override;

};