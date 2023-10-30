#include "containerThreads.h"


containerThreads::containerThreads(Socket &peer,Queue<Snapshot> &acciones,Queue<Comando> &queue_comandos): skt(std::move(peer)){
    this->enviador = new Enviador(skt,queue_comandos);
    this->recibidor = new Recibidor(skt,acciones);

}

void containerThreads::start(){
    this->recibidor->start();
    this->enviador->start();
    
}

void containerThreads::join(){
    skt.close();
    this->enviador->join();
    this->recibidor->join();
}

containerThreads::~containerThreads(){
    delete this->enviador;
    delete this->recibidor;
}



