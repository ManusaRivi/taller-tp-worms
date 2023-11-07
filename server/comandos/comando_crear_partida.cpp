#include "comando_crear_partida.h"


CrearPartida::CrearPartida(uint8_t tipo, std::string nombre):nombre_partida(nombre),tipo_de_comando(tipo){

}


uint32_t CrearPartida::realizar_accion(Lobby &lobby, Queue<Mensaje>* snapshots, uint8_t responsable){
    std::string name;
    uint32_t num = 0;
    return num;
    //return lobby.crear_partida(nombre_partida,responsable,snapshots);
}