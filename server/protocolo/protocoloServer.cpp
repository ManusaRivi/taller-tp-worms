#include "protocoloServer.h"
#include "../comandos/comando.h"

Protocolo::Protocolo(Socket &socket): skt(socket){

}

Comando Protocolo::recibir_comando(bool &was_closed){
    uint8_t buf;
    skt.recvall(&buf,1,&was_closed);
    uint8_t cmd;
    if (buf == 0x01){
        skt.recvall(&cmd,1,&was_closed);
    }
    Comando comand = Comando(cmd,0x01);
    return comand;
    

}

void Protocolo::enviar_snapshot(Snapshot snap){
    std::vector<uint8_t> buf;
    buf.push_back(0x01);
    uint8_t cant_players = 2;
    buf.push_back(cant_players);
    std::vector<Worm> worms = snap.get_worms();
    uint8_t id = 0;
    uint8_t cant_items = 2;
    bool was_closed = false;
    for (auto &c: worms){
        buf.push_back(id);
        std::vector<float> posicion = c.get_position();
        uint8_t pos_x = posicion[0]*100;
        uint8_t pos_y = posicion[1]*100;
        std::cout << "Se envia por socket la posicion (x,y) = [ " << unsigned(pos_x) << "," << unsigned(pos_y) << "]" << std::endl;
        buf.push_back(pos_x);
        buf.push_back(pos_y);
        id++;
        cant_items = cant_items +3;
        
    }
    skt.sendall(buf.data(),cant_items,&was_closed);

}
