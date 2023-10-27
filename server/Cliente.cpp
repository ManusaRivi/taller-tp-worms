#include "Cliente.h"


Cliente::Cliente(Socket &peer):skt(peer){

    this->recibidor = new Recibidor(skt);

}

void Cliente::start(){
    recibidor->start();
}


bool Cliente::is_dead(){
    return this->recibidor->is_dead();
}

void Cliente::join(){
    this->recibidor->join();
}