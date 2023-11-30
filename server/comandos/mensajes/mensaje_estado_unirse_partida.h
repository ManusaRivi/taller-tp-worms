#include "mensaje.h"


class MensajeEstadoUnirse:public MensajeServer{
    uint8_t estado;


    public:
    MensajeEstadoUnirse(uint8_t state);
    uint8_t& get_state();
};
