#include "containerThreads.h"


containerThreads::containerThreads(Socket &peer,Queue<std::shared_ptr<Mensaje>> &acciones,Queue<std::shared_ptr<Mensaje>> &queue_comandos): skt(std::move(peer)),enviador(skt,queue_comandos),recibidor(skt,acciones){

}

// No hace falta new en cliente;

void containerThreads::start(){
    this->recibidor.start();
    this->enviador.start();
    
}

void containerThreads::join(){
    skt.close();
    this->enviador.join();
    this->recibidor.join();
}

containerThreads::~containerThreads(){

}



