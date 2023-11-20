#include "mensaje_cliente.h"
#include <vector>

class MensajeHandshakeEnviar:public MensajeCliente{


    uint32_t id_player;
    std::vector<uint32_t> id_gusanos;

    public:
    MensajeHandshakeEnviar(uint32_t id_player_, std::vector<uint32_t> id_gusanos_);

    uint32_t get_player();

    std::vector<uint32_t> get_gusanos();

};