#include "threadRecibidor.h"

Recibidor::Recibidor(Socket &peer, Queue<std::shared_ptr<Comando>> &acciones_, uint8_t _id):skt(peer),acciones_a_realizar(acciones_), id(_id){

}


void Recibidor::run(){
    is_alive = true;
    bool was_closed = false;
    Protocolo ptcl(skt);
    while(!was_closed){
        std::shared_ptr<Comando> cmd = ptcl.recibir_comando(was_closed,id);
        acciones_a_realizar.push(cmd);

    }
    std::cout << "Se desconecto el cliente" << std::endl;
    is_alive = false;

}

bool Recibidor::is_dead(){
    return !is_alive;
}