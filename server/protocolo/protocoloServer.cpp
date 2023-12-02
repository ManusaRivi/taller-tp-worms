#include "protocoloServer.h"

ServerProtocolo::ServerProtocolo(Socket &socket): Protocolo(socket){

}

std::shared_ptr<Comando> ServerProtocolo::recibir_accion(uint32_t id){
    std::shared_ptr<Comando> comando;
    uint8_t buf = recibir_1_byte();
    switch(buf){
        case(CODIGO_MOVER):{
            uint8_t dir = recibir_1_byte();
            comando = factory.comando_movimiento(dir,id);
            break;
        }
        case(CODIGO_DETENER_MOVIMIENTO):{
            // printf("se recibe un codigo de detener el gusano\n");
            comando = factory.comando_detener(id);
            break;
        }
        case(CODIGO_CAMBIAR_ARMA):{
            uint8_t tipo = recibir_1_byte();
            // printf("Se recibe un cambio de arma con tipo = %u\n",tipo);
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
            // printf("Saltar con dir = %u\n",dir);
            comando = factory.comando_saltar(id,dir);
            break;
        }
        case(CODIGO_DISPARAR):{
            // printf("Se recibe un comando para disparar\n");
            comando = factory.comando_disparar(id);
            break;
        }
        case(CODIGO_CARGAR_ARMA):{
            // printf("Se recibe codigo para cargar arma\n");
            comando = factory.comando_cargar_arma(id);
            break;
        }
        case(CODIGO_DETENER_CAMBIO_ANGULO):{
            printf("Se recibe codigo para detener el cambio de angulo\n");
            comando = factory.comando_detener_angulo(id);
            break;
        }
        case (CODIGO_CAMBIAR_DIRECCION_APUNTADO):{
            // printf("Se recibe codigo par acambiar direccion de apuntado\n");
            uint8_t dir = recibir_1_byte();
            comando = factory.comando_cambia_direccion_arma(id,dir);
            break;
        }
        case (CODIGO_SETEAR_TARGET):{
            float x = recibir_4_bytes_float();
            float y = recibir_4_bytes_float();
            comando = factory.comando_setear_target(id,x,y);
            break;
        }
        case(CODIGO_SETEAR_TIMER):{
            uint32_t time = recibir_4_bytes();
            comando = factory.comando_setear_timer(id,time);
            break;
        }
    }
    return comando;


}

std::shared_ptr<MensajeServer> ServerProtocolo::recibir_comando(bool &was_closed, uint32_t id){
    std::shared_ptr<Comando> comando;
    uint8_t buf;
    skt.recvall(&buf,1,&was_closed);
    if (was_closed){
        throw ClosedSocket();
    }

    if (buf == CODIGO_CREAR_PARTIDA){
        std::string nombre = recibir_string();
        uint16_t id_mapa = recibir_2_bytes();
        // Mensaje msg(nombre,id_mapa);
        return mensajes.crear_partida(nombre,id_mapa);
    }
    if (buf == CODIGO_EMPEZAR_PARTIDA){
        // printf("Se recibe un codigo de empezar partida\n");
        // Mensaje msg;
        return mensajes.empezar_partida();
    }

    if (buf == CODIGO_LISTAR_PARTIDA){
        // printf("Se recibe pedido de listar partidas\n");
        // Mensaje msg(COMANDO::CMD_LISTAR_PARTIDAS);
        return mensajes.listar_partidas_recibidor();
    }

    if (buf == CODIGO_LISTAR_MAPAS) {
        // printf("Se recibe pedido de listar mapas\n");
        // Mensaje msg(COMANDO::CMD_LISTAR_MAPAS);
        return mensajes.listar_mapas_recibidor();
    }

    if (buf == CODIGO_UNIRSE_PARTIDA){
        // printf("Se recibe un pedido de unirse a partida");
        uint32_t id_partida = recibir_4_bytes();
        // Mensaje msg(COMANDO::CMD_UNIRSE_PARTIDA,id_partida);
        return mensajes.unirse_partida(id_partida);
    }

    if (buf == CODIGO_HANDSHAKE_EMPEZAR_PARTIDA){
        return recibir_id_gusanos();
    }
    return nullptr;
    

}

void ServerProtocolo::enviar_snapshot(std::shared_ptr<Snapshot> snap){
    std::shared_ptr<SnapshotPartida> snapshot = std::dynamic_pointer_cast<SnapshotPartida>(snap);
    uint8_t cmd = CODIGO_SNAPSHOT;
    enviar_1_byte(cmd);
    enviar_4_bytes(snapshot->get_gusano_actual());
    enviar_datos_especiales(snapshot->get_armas_especiales());
    enviar_gusanos(snapshot->get_worms());
    enviar_proyectiles(snapshot->get_proyectiles());
    enviar_explosiones(snapshot->get_explosiones());
    enviar_provisiones(snapshot->get_provisiones());
    enviar_sonidos(snapshot->get_sonidos());

}

void ServerProtocolo::enviar_partidas(std::map<uint32_t,std::string>& partidas/*std::string map*/){
    // printf("Se estan por enviar las partidas\n");
    //uint8_t cmd = CODIGO_LISTAR_PARTIDA;
    //enviar_1_byte(cmd);
    enviar_lista(partidas);
}

void ServerProtocolo::enviar_lista(std::map<uint32_t,std::string>& lista){
    uint16_t cantidad_mapas = lista.size();
    enviar_2_byte(cantidad_mapas);
    for (auto i = lista.begin(); i != lista.end(); i++){
        uint32_t id = i->first;

        std::string nombre = i->second;
        // std::cout << "Se envia un nombre " << nombre << std::endl;
        enviar_4_bytes(id);
        enviar_string(nombre);
        
    }
}

void ServerProtocolo::enviar_mapas(std::map<uint32_t,std::string>& mapas){
    enviar_lista(mapas);
}


void ServerProtocolo::check_partida_empezada(){
    uint8_t cmd = CODIGO_PARTIDA_POR_COMENZAR;
    enviar_1_byte(cmd);
}




void ServerProtocolo::enviar_handshake(std::pair<uint32_t,std::vector<uint32_t>>& gusanos_por_player, std::shared_ptr<Snapshot> snap){
    std::shared_ptr<SnapshotHandshake> snapshot = std::dynamic_pointer_cast<SnapshotHandshake>(snap);
    uint8_t cmd = CODIGO_HANDSHAKE_EMPEZAR_PARTIDA;
    uint16_t cantidad_gusanos = gusanos_por_player.second.size();
    enviar_1_byte(cmd);
    enviar_4_bytes(gusanos_por_player.first);
    enviar_2_byte(cantidad_gusanos);
    for(uint16_t i = 0; i < cantidad_gusanos;i++){ // Se envia el id de los gusanos que le pertenecen al player
        enviar_4_bytes(gusanos_por_player.second[i]);
    }
    enviar_4_bytes(snapshot->get_gusano_actual());
    enviar_gusanos(snapshot->get_worms());
    enviar_vigas(snapshot->get_vigas());
    // printf("Se termina de enviar handshake\n");
}




std::shared_ptr<MensajeServer> ServerProtocolo::recibir_id_gusanos(){
    uint32_t id_player = recibir_4_bytes();
    uint16_t cantidad_gusanos = recibir_2_bytes();
    std::vector<uint32_t> ids_gusanos;
    for (uint16_t i = 0; i < cantidad_gusanos;i++){
        ids_gusanos.push_back(recibir_4_bytes());
    }
    std::pair<uint32_t,std::vector<uint32_t>> par(id_player,ids_gusanos);
    // Mensaje msg(par);
    return mensajes.handshake_recibir(par);
}



void ServerProtocolo::enviar_gusanos(std::vector<WormWrapper>& worms){
    uint8_t cant_players = worms.size();  
    enviar_2_byte(cant_players);
    // printf("La cantidad de gusanops que se envian es %u\n",cant_players);
    for (auto &c: worms){
        uint32_t id = c.get_id();
        std::vector<float> posicion = c.get_position();
        float angulo = c.get_angulo();
        uint8_t direccion = c.get_direccion();
        uint8_t estado = c.get_estado();
        float angulo_disparo = c.get_angulo_disparo() + 1.57;
        uint8_t vida = c.get_vida();
        uint32_t equipo = c.get_equipo();

        enviar_4_bytes(id);
        enviar_4_bytes_float(posicion[0]);
        enviar_4_bytes_float(posicion[1]);
        
        enviar_4_bytes_float(angulo);
        enviar_1_byte(direccion);
        enviar_1_byte(estado);
        enviar_4_bytes_float(angulo_disparo);
        enviar_1_byte(vida);
        enviar_4_bytes(equipo);

    }
}


void ServerProtocolo::enviar_vigas(std::vector<std::vector<float>>& vigas){

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



void ServerProtocolo::enviar_proyectiles(std::vector<ProjectileWrapper>& proyectiles){
    uint16_t cantidad = proyectiles.size();
    enviar_2_byte(cantidad);
    // printf("La cantidad de proyectiles que se envian es %u\n",cantidad);
    for(auto c : proyectiles){
        uint32_t id = c.get_id();
        float x = c.get_x();
        float y = c.get_y();
        float angle = c.get_angulo() + 1.57;
        uint8_t tipo = c.get_tipo();

        enviar_4_bytes(id);
        enviar_4_bytes_float(x);
        enviar_4_bytes_float(y);
        enviar_4_bytes_float(angle);
        enviar_1_byte(tipo);

        // printf("El proyectil que se manda es de %f    %f    %f    tipo = %u",x,y,angle,tipo);

    }
}


void ServerProtocolo::enviar_explosiones(std::vector<ExplosionWrapper>& explosiones){
    uint16_t cantidad = explosiones.size();
    enviar_2_byte(cantidad);
    // printf("La cantidad de explosiones que se envian es %u\n",cantidad);
    for(auto c : explosiones){
        uint32_t id = c.get_id();
        float x = c.get_x();
        float y = c.get_y();
        float radio = c.get_radius();

        enviar_4_bytes(id);
        enviar_4_bytes_float(x);
        enviar_4_bytes_float(y);
        enviar_4_bytes_float(radio);

    }
}

void ServerProtocolo::enviar_provisiones(std::vector<ProvisionWrapper>& provisiones) {
    uint16_t cantidad = provisiones.size();
    enviar_2_byte(cantidad);
    for(auto c : provisiones){
        uint32_t id = c.get_id();
        float x = c.get_x();
        float y = c.get_y();

        enviar_4_bytes(id);
        enviar_4_bytes_float(x);
        enviar_4_bytes_float(y);
    }
}

void ServerProtocolo::enviar_sonidos(std::vector<SoundTypes>& sonidos){
    uint16_t cantidad = sonidos.size();
    enviar_2_byte(cantidad);
    for (uint8_t sonido : sonidos) {
        enviar_1_byte(sonido);
    }
}

void ServerProtocolo::enviar_estado_unirse(uint8_t estado){
    uint8_t cd = CODIGO_ESTADO_UNIRSE_PARTIDA;
    enviar_1_byte(cd);
    enviar_1_byte(estado);
}

void ServerProtocolo::enviar_datos_especiales(std::vector<std::pair<uint8_t,std::vector<float>>>& datos){
    auto& [has_tp, pos_tp] = datos[0];
    auto& [has_ataque_aereo, pos_ataque] = datos[1];
    auto& [has_timer, timer] = datos[2];


    enviar_1_byte(has_tp); 
    enviar_4_bytes_float(pos_tp[0]); 
    enviar_4_bytes_float(pos_tp[1]); // { 0 Si no tiene/1 si, x pos, y pos}
    enviar_1_byte(has_ataque_aereo); 
    enviar_4_bytes_float(pos_ataque[0]);
    enviar_4_bytes_float(pos_ataque[1]);
    enviar_1_byte(has_timer);
    enviar_4_bytes(timer[0]);

}