#include "threadRecibidor.h"

Recibidor::Recibidor(Socket &peer, Queue<std::shared_ptr<Comando>> &acciones_,Queue<Mensaje>* snapshots_,Lobby &lobby_):skt(peer),
                                                                                                                        acciones_a_realizar(acciones_), 
                                                                                                                        snapshots(snapshots_),
                                                                                                                        id_partida(0),
                                                                                                                        lobby(lobby_){

}


void Recibidor::run()try{{
    is_alive = true;
    bool was_closed = false;
    ServerProtocolo ptcl(skt);
    Queue<std::shared_ptr<Comando>> cola;
    //bool esta_en_partida = false;
    while(is_alive){
        Mensaje msg = ptcl.recibir_comando(was_closed,id);
        if(msg.tipo_mensaje() == COMANDO::CMD_CREAR_PARTIDA){
            printf("Se recibe un mensaje para crear partdia\n");
            uint32_t id_partida_queue = lobby.crear_partida(msg.nombre_mapa,snapshots); 
            id_partida = id_partida_queue;
        }

        if(msg.tipo_mensaje() == COMANDO::CMD_LISTAR_PARTIDAS){
            printf("Se recibe pedido de listar partidas en recibidor\n");
            lobby.listar_partidas(snapshots);
        }

        if(msg.tipo_mensaje() == COMANDO::CMD_LISTAR_MAPAS){
            printf("Se recibe pedido de listar mapas\n");
            lobby.listar_mapas(snapshots);
        }

        if (msg.tipo_mensaje() == COMANDO::CMD_EMPEZAR_PARTIDA){
            printf("Se recibe comando de empezar partida\n");
            Queue<std::shared_ptr<Comando>> &queue_acciones = lobby.get_queue(id_partida);
            FactoryComandos factory;
            queue_acciones.push(factory.comando_empezar());
        }
        if(msg.tipo_mensaje() == COMANDO::CMD_UNIRSE_PARTIDA){
            lobby.unirse_a_partida(msg.id_partida_a_unirse,snapshots);
            this->id_partida = msg.id_partida_a_unirse;
        }
        if (msg.tipo_mensaje() == COMANDO::CMD_HANDSHAKE){

            std::pair<uint32_t,std::vector<uint32_t>> id_gusanos = msg.gusanos_por_player;
            this->id_gusanos = id_gusanos.second;
            this->id = id_gusanos.first;
            break;
        }
    }
    if(is_alive && id_partida > 0){
        bool partida_online = true;
        Queue<std::shared_ptr<Comando>> &queue_acciones = lobby.get_queue(id_partida);
        while(partida_online && is_alive){
            std::shared_ptr<Comando> cmd = ptcl.recibir_accion(id);
            queue_acciones.push(cmd);
        }
    }

    std::cout << "Se desconecto el cliente" << std::endl;
    is_alive = false;

}}catch(const ClosedSocket& e){
    printf("El recibidor se desconecta i se saca al player de la partida\n");
    if(id_partida > 0 && is_alive){
        lobby.desconectarse_partida(id_partida,snapshots);
    }
    is_alive = false;
    snapshots->close();

}

bool Recibidor::is_dead(){
    return !is_alive;
}

void Recibidor::kill_thread(){
    is_alive = false;
}