#include "mensaje.h"

class MensajePartidaTermino:public MensajeServer{

    
    uint32_t equipo_ganador;
    bool fue_empate;
    public:
    MensajePartidaTermino(uint32_t equipo_ganador, bool fue_emapte);

    uint32_t get_equipo_ganador();
    bool fue_empate_();

};