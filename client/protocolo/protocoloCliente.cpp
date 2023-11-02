#include "protocoloCliente.h"
#include "../../common/socket.h"
#include "../snapshot.h"

#define MOVER_GUSANO 0x01
#define DETENER_MOVIMIENTO 0x02

Protocolo::Protocolo(Socket &peer):skt(peer) {
            was_closed = false;
        }

Protocolo::~Protocolo() {}

void Protocolo::enviar_movimiento(uint8_t dir){
    bool was_closed = false;
    std::vector<uint8_t> buf;
    buf.push_back(MOVER_GUSANO);
    buf.push_back(dir);
    skt.sendall(buf.data(),2,&was_closed);
}

void Protocolo::detener_movimiento(){
    bool was_closed = false;
    std::vector<uint8_t> buf;
    buf.push_back(DETENER_MOVIMIENTO);
    skt.sendall(buf.data(),1,&was_closed);
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

        float x_pos = worm_format[1];
        float y_pos = worm_format[2];
        float xpos = x_pos/100;
        float ypos = y_pos/100;
        std::cout << " ID = [ " << unsigned(worm_format[0]) <<"] (X, Y) =  (" << x_pos << " , " << y_pos<< ") (en centimetros)"<<std::endl;
        std::vector<float> pos;
        pos.push_back(xpos);
        pos.push_back(ypos);
        std::cout << " Y Se transforma en la posicion (X, Y) =  (" << xpos << " , " << ypos <<") (en metros)" <<std::endl;
        Worm worm(pos,1,0);
        sn.add_worm(worm);
    }
    return sn;
}

