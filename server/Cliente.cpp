#include "Cliente.h"


Cliente::Cliente(Socket &peer, uint8_t identificador, Queue<Snapshot>* caster, Queue<std::shared_ptr<Comando>> &acciones):skt(std::move(peer)),id(identificador),snapshots_a_enviar(caster){

    this->recibidor = new Recibidor(skt, acciones,id);
    this->enviador = new Enviador(skt,id, snapshots_a_enviar );

}

void Cliente::start(){
    enviador->start();
    recibidor->start();
}


bool Cliente::is_dead(){
    return this->recibidor->is_dead();
}

void Cliente::join(){
    this->recibidor->join();
    this->enviador->join();
}