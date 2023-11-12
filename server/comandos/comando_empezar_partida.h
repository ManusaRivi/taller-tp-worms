#ifndef _CREAR_PARTIDA
#define _CREAR_PARTIDA
#include "comando.h"

class EmpezarPartida:public Comando{

    std::string nombre_partida;
    uint8_t tipo_de_comando;

    public:
    EmpezarPartida();

    void agregar_id(uint8_t id) override;
    void realizar_accion(Mapa &mapa);

    uint8_t get_comando() override;
};

#endif