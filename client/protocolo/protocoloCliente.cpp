#include "protocoloCliente.h"
#include "../../common/socket.h"

Protocolo::Protocolo(const std::string& hostname, const std::string& servname):
        hostname(hostname), skt(hostname.c_str(), servname.c_str()) {
            was_closed = false;
        }

Protocolo::~Protocolo() {}

void Protocolo::enviar_movimiento(uint8_t dir){

    bool was_closed = false;
    skt.sendall(&dir,1,&was_closed);
}