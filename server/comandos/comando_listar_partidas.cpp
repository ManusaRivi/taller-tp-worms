#include "comando_listar_partidas.h"


ListarPartidas::ListarPartidas(){

}

void ListarPartidas::realizar_accion(Lobby& lobby,Queue<Snapshot>* snapshots, uint8_t responsable){
    return;
}


uint8_t ListarPartidas::get_comando(){
    return this->tipo_comando;
}
