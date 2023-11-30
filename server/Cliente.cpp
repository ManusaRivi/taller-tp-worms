#include "Cliente.h"


Cliente::Cliente(Socket &peer, Queue<std::shared_ptr<Comando>> &acciones,Lobby &lobby_):skt(std::move(peer)),
                                                                                        snapshots_a_enviar(new Queue<std::shared_ptr<MensajeServer>>),
                                                                                        lobby(lobby_){

    this->recibidor = new Recibidor(skt, acciones,snapshots_a_enviar,lobby);
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

void Cliente::kill(){
    if(!recibidor->is_dead()){
        skt.shutdown(2);
        skt.close();
    }

    recibidor->kill_thread();
}

Cliente::~Cliente(){
    delete this->enviador;
    delete this->recibidor;
    delete snapshots_a_enviar;
}
