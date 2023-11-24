#include "mensaje.h"


class MensajeHandshakeRecibir:public MensajeServer{
    std::pair<uint32_t,std::vector<uint32_t>> id_gusanos;


    public:
    MensajeHandshakeRecibir(std::pair<uint32_t,std::vector<uint32_t>> id_gusanos_);
    std::pair<uint32_t,std::vector<uint32_t>> get_pair();
};
