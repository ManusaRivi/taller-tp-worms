#include "protocoloServer.h"

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

    if (buf == CODIGO_HANDSHAKE_EMPEZAR_PARTIDA){
        return recibir_id_gusanos();
    }
    Mensaje msg;
    return msg;
    

}

void ServerProtocolo::enviar_snapshot(Snapshot snap){
    uint8_t cmd = CODIGO_SNAPSHOT;
    enviar_1_byte(cmd);

    uint32_t turno_current_gusano = snap.get_gusano_jugador();
    enviar_4_bytes(turno_current_gusano);

    uint8_t cant_players = 2;
    enviar_2_byte(cant_players);
    std::vector<WormWrapper> worms = snap.get_worms();
    for (auto &c: worms){
        uint32_t id = c.get_id();
        std::vector<float> posicion = c.get_position();
        uint32_t angulo = c.get_angulo();
        uint8_t direccion = c.get_direccion();
        uint8_t estado = c.get_estado();

        enviar_4_bytes(id);
        enviar_4_bytes_float(posicion[0]);
        enviar_4_bytes_float(posicion[1]);
        enviar_4_bytes(angulo);
        enviar_1_byte(direccion);
        enviar_1_byte(estado);

    }

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
    uint8_t cmd = CODIGO_PARTIDA_POR_COMENZAR;
    enviar_1_byte(cmd);
}

void ServerProtocolo::enviar_vigas(Snapshot& snap){
    std::vector<std::vector<int>> vigas = snap.get_vigas();

    uint16_t cantidad_vigas = vigas.size();
    uint32_t tamanio_buffer = cantidad_vigas*(4+4+4+4); //Cada viga tiene 4 bytes para x, 4 para y, 4 para angulo, 4 para tamanio
    std::vector<uint8_t> buffer(tamanio_buffer,0);
    for(uint16_t i = 0; i < cantidad_vigas; i++ ){
        std::vector<int> viga = vigas[i];   
        enviar_4_bytes(viga[0]);
        enviar_4_bytes(viga[1]);
        enviar_4_bytes(viga[2]);
        enviar_4_bytes(viga[3]);
    }
}

void ServerProtocolo::enviar_handshake(std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player){
    uint8_t cmd = CODIGO_HANDSHAKE_EMPEZAR_PARTIDA;
    uint16_t cantidad_gusanos = gusanos_por_player.second.size();
    enviar_1_byte(cmd);
    enviar_4_bytes(gusanos_por_player.first);
    enviar_2_byte(cantidad_gusanos);
    for(uint16_t i = 0; i < cantidad_gusanos;i++){
        enviar_4_bytes(gusanos_por_player.second[i]);
    }
}

Mensaje ServerProtocolo::recibir_id_gusanos(){
    uint32_t id_player = recibir_4_bytes();
    uint16_t cantidad_gusanos = recibir_2_bytes();
    std::vector<uint32_t> ids_gusanos;
    for (uint16_t i = 0; i < cantidad_gusanos;i++){
        ids_gusanos.push_back(recibir_4_bytes());
    }
    std::pair<uint32_t,std::vector<uint32_t>> par(id_player,ids_gusanos);
    Mensaje msg(par);
    return msg;
}