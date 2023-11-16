#include "threadRecibidor.h"


Recibidor::Recibidor(Socket &peer, Queue<std::shared_ptr<Mensaje>> &acciones):skt(peer),snapshots_a_render(acciones){

}


void Recibidor::run(){
    bool was_closed = false;
    ClienteProtocolo ptcl(skt);
    while(!was_closed){
        std::shared_ptr<Mensaje> sn = ptcl.recibir_snapshot();
        if(!sn){
            continue;
        }
        snapshots_a_render.push(sn);
    }
}