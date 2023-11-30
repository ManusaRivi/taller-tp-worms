#include "mensaje_listar_partidas.h"


MensajeListarPartidas::MensajeListarPartidas(std::map<uint32_t,std::string> lista_):MensajeServer(COMANDO::CMD_LISTAR_PARTIDAS),lista(lista_){
    
}


MensajeListarPartidas::MensajeListarPartidas():MensajeServer(COMANDO::CMD_LISTAR_PARTIDAS){

}


std::map<uint32_t,std::string>& MensajeListarPartidas::get_lista(){
    return this->lista;
}