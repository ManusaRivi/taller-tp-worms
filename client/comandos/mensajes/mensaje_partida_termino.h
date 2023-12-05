#include "mensaje_cliente.h"


class MensajePartidaTermino:public MensajeCliente{


    uint32_t equipo_ganador;
    bool fue_empate;
    public:
    MensajePartidaTermino( uint32_t equipo_ganador, bool fue_empate);

    uint32_t get_equipo_ganador();
    bool fue_empate_();
};