#include "threadRecibidor.h"

Recibidor::Recibidor(Socket &peer, Queue<std::shared_ptr<Comando>> &acciones_,Queue<std::shared_ptr<MensajeServer>>* snapshots_,Lobby &lobby_):skt(peer),
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
        std::shared_ptr<MensajeServer> msg = ptcl.recibir_comando(was_closed,id);
        if(!msg){
            continue;
        }
        if(msg->get_tipo() == COMANDO::CMD_CREAR_PARTIDA){
            std::shared_ptr<MensajeCrearPartida> crear = std::dynamic_pointer_cast<MensajeCrearPartida>(msg);
            // printf("Se recibe un mensaje para crear partdia\n");
            uint32_t id_partida_queue = lobby.crear_partida(crear->get_nombre_partida(),snapshots,crear->get_id_mapa()); 
            id_partida = id_partida_queue;
        }

        else if(msg->get_tipo() == COMANDO::CMD_LISTAR_PARTIDAS){
            
            // printf("Se recibe pedido de listar partidas en recibidor\n");
            std::map<uint32_t,std::string> lista = lobby.listar_partidas(snapshots);
            std::shared_ptr<MensajeServer> mensaje_lista = mensajes.listar_partidas(lista);
            snapshots->push(mensaje_lista);

        }

        else if(msg->get_tipo() == COMANDO::CMD_LISTAR_MAPAS){
            std::map<uint32_t,std::string> lista = this->lobby.listar_mapas(snapshots);
            std::shared_ptr<MensajeServer> mensaje_lista = mensajes.listar_partidas(lista);
            snapshots->push(mensaje_lista);
        }

        else if (msg->get_tipo() == COMANDO::CMD_EMPEZAR_PARTIDA){
            // printf("Se recibe comando de empezar partida\n");
            Queue<std::shared_ptr<Comando>> &queue_acciones = lobby.get_queue(id_partida);
            FactoryComandos factory;
            queue_acciones.push(factory.comando_empezar());
        }
        else if(msg->get_tipo() == COMANDO::CMD_UNIRSE_PARTIDA){
            std::shared_ptr<MensajeUnirsePartida> unirse = std::dynamic_pointer_cast<MensajeUnirsePartida>(msg);
            bool estado = lobby.unirse_a_partida(unirse->get_id_partida(),snapshots);
            uint8_t se_unio;
            if(estado == false){
                se_unio = 0;
            }
            else{
                se_unio = 1;
                this->id_partida = unirse->get_id_partida();
                id++;
            }
            std::shared_ptr<MensajeServer> mensaje = mensajes.estado_unirse_partida(se_unio);
            snapshots->push(mensaje);

        }

        else if (msg->get_tipo() == COMANDO::CMD_HANDSHAKE){
            std::shared_ptr<MensajeHandshakeRecibir> par = std::dynamic_pointer_cast<MensajeHandshakeRecibir>(msg);
            std::pair<uint32_t,std::vector<uint32_t>> id_gusanos = par->get_pair();
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
            if(!cmd){
                continue;
            }
            queue_acciones.push(cmd);
        }
    }

    // std::cout << "Se desconecto el cliente" << std::endl;
    is_alive = false;

}}catch(const ClosedSocket& e){
    // printf("El recibidor se desconecta i se saca al player de la partida\n");
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