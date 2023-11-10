#include "protocoloServer.h"
#include "../comandos/comando.h"

ServerProtocolo::ServerProtocolo(Socket &socket): Protocolo(socket){

}

Mensaje ServerProtocolo::recibir_comando(bool &was_closed, uint8_t id){
    std::shared_ptr<Comando> comando;
    uint8_t buf;
    skt.recvall(&buf,1,&was_closed);
    uint8_t cmd;

    if (buf == CODIGO_MOVER){
        printf("Se recibe un codigo de mover el gusano\n");
        skt.recvall(&cmd,1,&was_closed);
        comando = factory.comando_movimiento(cmd,id);
        Mensaje msg(comando);
        return msg;
    }

    if (buf == CODIGO_DETENER_MOVIMIENTO){
        printf("se recibe un codigo de detener el gusano\n");
        comando = factory.comando_detener();
        Mensaje msg(comando);
        return msg;
    }


    if (buf == CODIGO_CREAR_PARTIDA){
        std::string nombre = recibir_string();
        Mensaje msg(nombre);
        return msg;
    }
    if (buf == CODIGO_EMPEZAR_PARTIDA){
        printf("Se recibe un codigo de empezar partida\n");
        Mensaje msg;
        return msg;
    }

    if (buf == CODIGO_LISTAR_PARTIDA){
        printf("Se recibe pedido de listar partidas\n");
        Mensaje msg(COMANDO::CMD_LISTAR_PARTIDAS);
        return msg;
    }
    if (buf == CODIGO_UNIRSE_PARTIDA){
        printf("Se recibe un pedido de unirse a partida");
        uint32_t id_partida = recibir_4_bytes();
        Mensaje msg(COMANDO::CMD_UNIRSE_PARTIDA,id_partida);
        return msg;
    }
    Mensaje msg;
    return msg;
    

}

void ServerProtocolo::enviar_snapshot(Snapshot snap){
    std::vector<uint8_t> buf;
    buf.push_back(0x01);
    uint8_t cant_players = 2;
    buf.push_back(cant_players);
    std::vector<WormWrapper> worms = snap.get_worms();
    uint8_t id = 0;
    uint8_t cant_items = 2;
    bool was_closed = false;
    for (auto &c: worms){
        buf.push_back(id);
        std::vector<float> posicion = c.get_position();
        uint8_t pos_x = posicion[0]*100;
        uint8_t pos_y = posicion[1]*100;
        //std::cout << "Se envia por socket la posicion (x,y) = [ " << unsigned(pos_x) << "," << unsigned(pos_y) << "]" << std::endl;
        buf.push_back(pos_x);
        buf.push_back(pos_y);
        id++;
        cant_items = cant_items +3;
        
    }
    skt.sendall(buf.data(),cant_items,&was_closed);

}

void ServerProtocolo::enviar_partidas(std::map<uint32_t,std::string> map/*std::string map*/){
    printf("Se estan por enviar las partidas\n");
    //uint8_t cmd = CODIGO_LISTAR_PARTIDA;
    //enviar_1_byte(cmd);
    uint16_t cantidad_mapas = map.size();
    enviar_2_byte(cantidad_mapas);
    for (auto i = map.begin(); i != map.end(); i++){
        //uint32_t id = i->first;

        std::string nombre = i->second;
        //enviar_4_bytes(id);
        enviar_string(nombre);
        
    }
    //enviar_string(map);
}

void ServerProtocolo::check_partida_empezada(){
    printf("Se envia un comando que la partida esta por comenzar\n");
    uint8_t cmd = CODIGO_PARTIDA_POR_COMENZAR;
    enviar_1_byte(cmd);
}