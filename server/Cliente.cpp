#include "Cliente.h"


Cliente::Cliente(Socket &peer, uint8_t identificador, Queue<Mensaje>* caster, Queue<std::shared_ptr<Comando>> &acciones,Lobby &lobby_):skt(std::move(peer)),
                                                                                                                                        id(identificador),
                                                                                                                                        snapshots_a_enviar(caster),
                                                                                                                                        lobby(lobby_){

    this->recibidor = new Recibidor(skt, acciones,id,caster,lobby);
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

uint8_t Cliente::get_id(){
    return this->id;
}