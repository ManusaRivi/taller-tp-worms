#include "threadRecibidor.h"


Recibidor::Recibidor(Socket &peer, Queue<Mensaje> &acciones):skt(peer),snapshots_a_render(acciones){

}


void Recibidor::run(){
    bool was_closed = false;
    ClienteProtocolo ptcl(skt);
    while(!was_closed){
        Mensaje sn = ptcl.recibir_snapshot();
        snapshots_a_render.push(sn);
    }
}