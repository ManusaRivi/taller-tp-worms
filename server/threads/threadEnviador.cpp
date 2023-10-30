#include "threadEnviador.h"


Enviador::Enviador(Socket &peer, uint8_t _id, Queue<Snapshot> *snapshots):skt(peer), id(_id),snapshots_a_enviar(snapshots){

}


void Enviador::run(){
    bool was_closed = false;
    Protocolo ptcl(skt);
    while(!was_closed){
        Snapshot snap = snapshots_a_enviar->pop();
        ptcl.enviar_snapshot(snap);
    }
}