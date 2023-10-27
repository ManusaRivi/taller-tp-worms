#include "protocoloCliente.h"

Protocolo::Protocolo(Socket &socket_new):skt(socket_new){
    std::cout << "Se creo un protocolo" << std::endl;
}


void Protocolo::enviar_movimiento(uint8_t dir){

    bool was_closed = false;
    skt.sendall(&dir,1,&was_closed);
}