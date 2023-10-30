#include "threadRecibidor.h"


Recibidor::Recibidor(Socket &peer, Queue<Snapshot> &acciones):skt(peer),snapshots_a_render(acciones){

}


void Recibidor::run(){
    bool was_closed = false;
    Protocolo ptcl(skt);
    while(!was_closed){
        Snapshot sn = ptcl.recibir_snapshot();
        snapshots_a_render.push(sn);
    }
}