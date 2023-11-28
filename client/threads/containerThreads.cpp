#include "containerThreads.h"


containerThreads::containerThreads(Socket &peer,Queue<std::shared_ptr<MensajeCliente>> &acciones,Queue<std::shared_ptr<MensajeCliente>> &queue_comandos): skt(std::move(peer)),enviador(skt,queue_comandos),recibidor(skt,acciones,queue_comandos){

}

// No hace falta new en cliente;

void containerThreads::start(){
    this->recibidor.start();
    this->enviador.start();
    
}

void containerThreads::join(){
    skt.shutdown(2);
    skt.close();
    this->recibidor.kill();
    this->enviador.join();
    this->recibidor.join();
}

containerThreads::~containerThreads(){

}



