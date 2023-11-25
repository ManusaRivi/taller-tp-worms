#include "mensaje.h"

class MensajeUnirsePartida:public MensajeServer{

    uint32_t id_partida;

    public:
    MensajeUnirsePartida(uint32_t id_partida);

    uint32_t get_id_partida();

};