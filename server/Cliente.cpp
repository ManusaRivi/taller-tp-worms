#include "Cliente.h"


Cliente::Cliente(Socket &peer, Queue<Mensaje>* caster, Queue<std::shared_ptr<Comando>> &acciones,Lobby &lobby_):skt(std::move(peer)),
                                                                                                                                        snapshots_a_enviar(caster),
                                                                                                                                        lobby(lobby_){

    this->recibidor = new Recibidor(skt, acciones,caster,lobby);
    this->enviador = new Enviador(skt, snapshots_a_enviar );

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
