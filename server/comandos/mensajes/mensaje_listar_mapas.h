#include "mensaje.h"


class MensajeListarMapas:public MensajeServer{
    std::map<uint32_t,std::string> lista;


    public:
    MensajeListarMapas(std::map<uint32_t,std::string> lista_);
    MensajeListarMapas();
    std::map<uint32_t,std::string> get_lista();




};
