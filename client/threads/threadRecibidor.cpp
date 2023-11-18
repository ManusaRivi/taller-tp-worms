#include "threadRecibidor.h"


Recibidor::Recibidor(Socket &peer, Queue<std::shared_ptr<MensajeCliente>> &acciones,Queue<std::shared_ptr<MensajeCliente>> &queue_comandos_):skt(peer),snapshots_a_render(acciones),queue_comandos(queue_comandos_){

}


void Recibidor::run(){
    is_alive = true;
    ClienteProtocolo ptcl(skt);
    while(is_alive){
        std::shared_ptr<MensajeCliente> sn = ptcl.recibir_snapshot();
        if(!sn){
            continue;
        }
        snapshots_a_render.push(sn);
    }
}

void Recibidor::kill(){
    queue_comandos.close();
    snapshots_a_render.close();
    is_alive = false;
}