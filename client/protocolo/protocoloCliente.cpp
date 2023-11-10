#include "protocoloCliente.h"
#include "../../common/socket.h"
#include "../game/comunicacion/snapshot.h"



ClienteProtocolo::ClienteProtocolo(Socket &peer):Protocolo(peer) {
            was_closed = false;
        }


void ClienteProtocolo::enviar_movimiento(uint8_t dir){
    printf("Se envia un pedido de mover el gusano\n");
    bool was_closed = false;
    std::vector<uint8_t> buf;
    buf.push_back(CODIGO_MOVER);
    buf.push_back(dir);
    skt.sendall(buf.data(),2,&was_closed);
}

void ClienteProtocolo::detener_movimiento(){
    printf("Se envia una pedido de detener movimiento\n");
    bool was_closed = false;
    std::vector<uint8_t> buf;
    buf.push_back(CODIGO_DETENER_MOVIMIENTO);
    skt.sendall(buf.data(),1,&was_closed);
}


Mensaje ClienteProtocolo::recibir_snapshot(){
    bool was_closed = false;
    std::vector<std::vector<int>> vigas;
    Snapshot sn(vigas);
    uint8_t cmd;
    skt.recvall(&cmd,1,&was_closed);

    if(cmd == CODIGO_PARTIDA_POR_COMENZAR){
        Mensaje msg(COMANDO::CMD_PARTIDA_EMPEZO);
        return msg;
    }
    if(cmd == CODIGO_LISTAR_PARTIDA){
        std::map<uint32_t,std::string> map = listar_partidas();
        Mensaje msg(map);
        return msg;
    }
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
        //std::cout << " ID = [ " << unsigned(worm_format[0]) <<"] (X, Y) =  (" << x_pos << " , " << y_pos<< ") (en centimetros)"<<std::endl;
        std::vector<float> pos;
        pos.push_back(xpos);
        pos.push_back(ypos);
        //std::cout << " Y Se transforma en la posicion (X, Y) =  (" << xpos << " , " << ypos <<") (en metros)" <<std::endl;
        Worm worm(pos,1,1);
        sn.add_worm(worm);
    }
    Mensaje msg(sn);
    return sn;
}

void ClienteProtocolo::crear_partida(std::string nombre){
    uint8_t cmd = CODIGO_CREAR_PARTIDA;
    enviar_1_byte(cmd);
    enviar_string(nombre);
}

void ClienteProtocolo::empezar_partida(){
    uint8_t cmd = CODIGO_EMPEZAR_PARTIDA;
    enviar_1_byte(cmd);
}


std::map<uint32_t,std::string> ClienteProtocolo::listar_partidas(){
    std::map<uint32_t,std::string> map;
    
    uint16_t size = recibir_2_bytes();
    uint32_t id_mapa = 1;
    for(uint16_t i = 0; i < size; i++ ){
        //uint32_t id_mapa = recibir_4_bytes();
        std::string nombre_mapa = recibir_string();
        map.insert({id_mapa,nombre_mapa});
        id_mapa++;
    }
    return map;
    
    //std::string nombreMapa = recibir_string();
    //map.insert({1,nombreMapa});
    //return map;
}

void ClienteProtocolo::pedir_lista_partidas(){
    uint8_t cmd = CODIGO_LISTAR_PARTIDA;
    enviar_1_byte(cmd);
}

void ClienteProtocolo::unirse_partida(std::string id_partida){
    uint32_t id = static_cast<uint32_t>(std::stoul(id_partida));
    uint8_t cmd = CODIGO_UNIRSE_PARTIDA;
    enviar_1_byte(cmd);
    enviar_4_bytes(id);
}
