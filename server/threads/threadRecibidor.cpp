#include "threadRecibidor.h"

Recibidor::Recibidor(Socket &peer, Queue<std::shared_ptr<Comando>> &acciones_, uint8_t _id,Queue<Mensaje>* snapshots_,Lobby &lobby_):skt(peer),
                                                                                                                        acciones_a_realizar(acciones_), 
                                                                                                                        id(_id),
                                                                                                                        snapshots(snapshots_),
                                                                                                                        id_partida(0),
                                                                                                                        lobby(lobby_){

}


void Recibidor::run(){
    is_alive = true;
    bool was_closed = false;
    ServerProtocolo ptcl(skt);
    //bool esta_en_partida = false;
    while(!was_closed){
        Mensaje msg = ptcl.recibir_comando(was_closed,id);

        if(msg.tipo_mensaje() == COMANDO::CMD_ACCION_JUGADOR){
            printf("Se popea en el recibidor una accion del jugador\n");
            //std::cout << "Se recibe una accion de mover del jugador  = " << unsigned(id) << "Para mover al gusano" << unsigned(id_gusano) << std::endl; 
            Queue<std::shared_ptr<Comando>> &queue_acciones = lobby.get_queue(id_partida);
            std::shared_ptr<Comando> cmd = msg.cmd;
            cmd.get()->id_gusano = id_gusano;
            queue_acciones.push(cmd);
        }
        if(msg.tipo_mensaje() == COMANDO::CMD_CREAR_PARTIDA){
            std::pair<uint32_t,uint8_t> id_partida_gusano = lobby.crear_partida(msg.nombre_mapa,id,snapshots);
            this->id_partida = id_partida_gusano.first;
            this->id_gusano = id_partida_gusano.second; 
        }

        if(msg.tipo_mensaje() == COMANDO::CMD_LISTAR_PARTIDAS){
            printf("Se recibe pedido de listar partidas en recibidor\n");
            lobby.listar_partidas(snapshots);
        }

        if (msg.tipo_mensaje() == COMANDO::CMD_EMPEZAR_PARTIDA){
            printf("Se recibe comando de empezar partida\n");
            lobby.empezar_partida(id_partida);
        }
        if(msg.tipo_mensaje() == COMANDO::CMD_UNIRSE_PARTIDA){
            this->id_gusano = lobby.unirse_a_partida(msg.id_partida_a_unirse,snapshots,id);
            this->id_partida = msg.id_partida_a_unirse;
            std::cout << "El id del gusano al unirse es " << unsigned(id_gusano) << std::endl;
        }
        if(msg.tipo_mensaje() == COMANDO::CMD_LISTAR_MAPAS) {
            printf("Se recibe pedido de listar mapas en recibidor\n");
            lobby.listar_mapas(snapshots);
        }

    }
    std::cout << "Se desconecto el cliente" << std::endl;
    is_alive = false;

}

bool Recibidor::is_dead(){
    return !is_alive;
}