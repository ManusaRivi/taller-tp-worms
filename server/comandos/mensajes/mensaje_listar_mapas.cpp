#include "mensaje_listar_mapas.h"


MensajeListarMapas::MensajeListarMapas(std::map<uint32_t,std::string> lista_):MensajeServer(COMANDO::CMD_LISTAR_MAPAS),lista(lista_){
    
}

MensajeListarMapas::MensajeListarMapas():MensajeServer(COMANDO::CMD_LISTAR_MAPAS){

}

std::map<uint32_t,std::string>& MensajeListarMapas::get_lista(){
    return this->lista;
}