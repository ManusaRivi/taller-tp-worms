#include "protocoloServer.h"

ServerProtocolo::ServerProtocolo(Socket &socket): Protocolo(socket){

}

std::shared_ptr<Comando> ServerProtocolo::recibir_accion(uint32_t id)try{{
    std::shared_ptr<Comando> comando;
    uint8_t buf = recibir_1_byte();
    switch(buf){
        case(CODIGO_MOVER):{
            uint8_t dir = recibir_1_byte();
            comando = factory.comando_movimiento(dir,id);
            break;
        }
        case(CODIGO_DETENER_MOVIMIENTO):{
            printf("se recibe un codigo de detener el gusano\n");
            comando = factory.comando_detener(id);
            break;
        }
        case(CODIGO_CAMBIAR_ARMA):{
            uint8_t tipo = recibir_1_byte();
            printf("Se recibe un cambio de arma con tipo = %u\n",tipo);
            comando = factory.comando_cambiar_arma(id,tipo);
            break;
        }
        case(CODIGO_CAMBIAR_ANGULO):{
            uint8_t dir = recibir_1_byte();
            printf("Cambiar Angul con direccion = %u\n",dir);
            comando = factory.comando_cambiar_angulo(id,dir);
            break;
        }
        case(CODIGO_SALTAR):{
            uint8_t dir = recibir_1_byte();
            printf("Saltar con dir = %u\n",dir);
            comando = factory.comando_saltar(id,dir);
            break;
        }
        case(CODIGO_DISPARAR):{
            printf("Se recibe un comando para disparar\n");
            comando = factory.comando_disparar(id);
            break;
        }
        case(CODIGO_CARGAR_ARMA):{
            printf("Se recibe codigo para cargar arma\n");
            comando = factory.comando_cargar_arma(id);
            break;
        }
        case(CODIGO_DETENER_CAMBIO_ANGULO):{
            printf("Se recibe codigo para mover el angulo para arriba\n");
            comando = factory.comando_detener_angulo(id);
            break;
        }
    }
    return comando;


}}catch(const ClosedSocket& e){
    throw ClosedSocket();
}

Mensaje ServerProtocolo::recibir_comando(bool &was_closed, uint32_t id)try{{
    std::shared_ptr<Comando> comando;
    uint8_t buf;
    skt.recvall(&buf,1,&was_closed);
    if (was_closed){
        throw ClosedSocket();
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

    if (buf == CODIGO_LISTAR_MAPAS) {
        printf("Se recibe pedido de listar mapas\n");
        Mensaje msg(COMANDO::CMD_LISTAR_MAPAS);
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
    

}}catch(const ClosedSocket& e){
    throw ClosedSocket();
}

void ServerProtocolo::enviar_snapshot(Snapshot snap)try{{
    uint8_t cmd = CODIGO_SNAPSHOT;
    enviar_1_byte(cmd);
    enviar_gusanos(snap);

}}catch(const ClosedSocket& e){
    throw ClosedSocket();
}

void ServerProtocolo::enviar_partidas(std::map<uint32_t,std::string> partidas/*std::string map*/){
    printf("Se estan por enviar las partidas\n");
    //uint8_t cmd = CODIGO_LISTAR_PARTIDA;
    //enviar_1_byte(cmd);
    enviar_lista(partidas);
}

void ServerProtocolo::enviar_lista(std::map<uint32_t,std::string> lista){
    uint16_t cantidad_mapas = lista.size();
    enviar_2_byte(cantidad_mapas);
    for (auto i = lista.begin(); i != lista.end(); i++){
        uint32_t id = i->first;

        std::string nombre = i->second;
        std::cout << "Se envia un nombre " << nombre << std::endl;
        enviar_4_bytes(id);
        enviar_string(nombre);
        
    }
}

void ServerProtocolo::enviar_mapas(std::map<uint32_t,std::string> mapas){
    printf("Se estan por enviar los mapas\n");
    enviar_lista(mapas);
}

void ServerProtocolo::check_partida_empezada(){
    uint8_t cmd = CODIGO_PARTIDA_POR_COMENZAR;
    enviar_1_byte(cmd);
}



void ServerProtocolo::enviar_handshake(std::pair<uint32_t,std::vector<uint32_t>> gusanos_por_player,Snapshot snap){
    uint8_t cmd = CODIGO_HANDSHAKE_EMPEZAR_PARTIDA;
    uint16_t cantidad_gusanos = gusanos_por_player.second.size();
    enviar_1_byte(cmd);
    enviar_4_bytes(gusanos_por_player.first);
    enviar_2_byte(cantidad_gusanos);
    for(uint16_t i = 0; i < cantidad_gusanos;i++){ // Se envia el id de los gusanos que le pertenecen al player
        enviar_4_bytes(gusanos_por_player.second[i]);
    }
    enviar_gusanos(snap);
    enviar_vigas(snap.get_vigas());
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


void ServerProtocolo::enviar_gusanos(Snapshot snap){
    uint32_t turno_current_gusano = snap.get_gusano_jugador();
    enviar_4_bytes(turno_current_gusano);

    
    std::vector<WormWrapper> worms = snap.get_worms();
    uint8_t cant_players = worms.size();  
    enviar_2_byte(cant_players);
    for (auto &c: worms){
        uint32_t id = c.get_id();
        std::vector<float> posicion = c.get_position();
        float angulo = c.get_angulo();
        uint8_t direccion = c.get_direccion();
        uint8_t estado = c.get_estado();
        float angulo_disparo = c.get_angulo_disparo();

        enviar_4_bytes(id);
        enviar_4_bytes_float(posicion[0]);
        enviar_4_bytes_float(posicion[1]);
        
        enviar_4_bytes_float(angulo);
        enviar_1_byte(direccion);
        enviar_1_byte(estado);
        enviar_4_bytes_float(angulo_disparo);

    }
}

void ServerProtocolo::enviar_vigas(std::vector<std::vector<float>> vigas){

    uint16_t cantidad_vigas = vigas.size();
    enviar_2_byte(cantidad_vigas);
    for(uint16_t i = 0; i < cantidad_vigas; i++ ){
        std::vector<float> viga = vigas[i];   
        enviar_4_bytes_float(viga[0]);
        enviar_4_bytes_float(viga[1]);
        enviar_4_bytes_float(viga[2]);
        enviar_4_bytes_float(viga[3]);
    }
}