#include "mensaje.h"

class MensajeCrearPartida:public MensajeServer{
    std::string nombre_partida;
    uint16_t id_mapa;

    public:
    MensajeCrearPartida(std::string nombre, uint16_t id_mapa);
    std::string get_nombre_partida();
    uint16_t get_id_mapa();
};