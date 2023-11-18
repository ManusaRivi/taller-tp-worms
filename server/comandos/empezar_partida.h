#ifndef _CREAR_PARTIDA
#define _CREAR_PARTIDA
#include "comando.h"

class EmpezarPartida:public Comando{

    std::string nombre_partida;
    uint8_t tipo_de_comando;

    public:
    EmpezarPartida();

    void realizar_accion(Mapa &mapa , uint32_t id);

};

#endif