#include "mensaje.h"


class MensajeListarPartidas:public MensajeServer{
    std::map<uint32_t,std::string> lista;


    public:
    MensajeListarPartidas(std::map<uint32_t,std::string> lista_);
    MensajeListarPartidas();
    std::map<uint32_t,std::string> get_lista();

};