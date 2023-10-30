#include "protocoloCliente.h"
#include "../../common/socket.h"
#include "../snapshot.h"

Protocolo::Protocolo(Socket &peer):skt(peer) {
            was_closed = false;
        }

Protocolo::~Protocolo() {}

void Protocolo::enviar_movimiento(uint8_t dir){
    std::cout << "Se intenta enviar movimient\n" << std::endl;
    bool was_closed = false;
    std::vector<uint8_t> buf;
    buf.push_back(0x01);
    buf.push_back(dir);
    if (dir == 0x01){
        std::cout << "Se envia la direccion de la derecha" << std::endl;
    }
    skt.sendall(buf.data(),2,&was_closed);
}


Snapshot Protocolo::recibir_snapshot(){
    bool was_closed = false;
    std::vector<std::vector<int>> vigas;
    Snapshot sn(vigas);
    uint8_t cmd;
    skt.recvall(&cmd,1,&was_closed);
    if (was_closed){
        return sn;
    }
    uint8_t cant_players;
    skt.recvall(&cant_players,1,&was_closed);
    for(uint8_t i = 0; i < cant_players; i++){
        std::vector<int> posicion;
        std::vector<uint8_t> worm_format(3,0);
        skt.recvall(worm_format.data(),3,&was_closed);

        int x_pos = worm_format[1];
        int y_pos = worm_format[2];
        float xpos = x_pos/100;
        float ypos = y_pos/100;
        std::cout << " Para el ID : " << unsigned(worm_format[0]) <<" Se imprime el int de x_pos " << x_pos << " Y la posicion Y " << y_pos<<std::endl;
        std::vector<float> pos;
        pos.push_back(worm_format[0]/100);
        pos.push_back(worm_format[1]/100);
        std::cout << " Y Se transforma en la posicion : " << xpos << "Y en la pos : " << ypos << std::endl;
        Worm worm(pos,1,0);
        sn.add_worm(worm);
    }
    return sn;
}


void Protocolo::enviar_comando(Comando cmd){
    if (cmd.tipo_comando == 0x01){
        enviar_movimiento(cmd.dir);
    }
}