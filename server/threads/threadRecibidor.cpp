#include "threadRecibidor.h"

Recibidor::Recibidor(Socket &peer):skt(peer){

}


void Recibidor::run(){
    is_alive = true;
    bool was_closed = false;
    while(!was_closed){
        uint8_t buf;

        skt.recvall(&buf,1, &was_closed);
        if (was_closed){
            break;
        }
        if (buf == 0x02){
            std::cout << "El personaje se movio a la izquierda" << std::endl;
        }
        if (buf == 0x01){
            std::cout << "El personaje se movio a la derecha" << std::endl;
        }
    }
    std::cout << "Se desconecto el cliente" << std::endl;
    is_alive = false;

}

bool Recibidor::is_dead(){
    return !is_alive;
}