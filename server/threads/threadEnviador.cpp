#include "threadEnviador.h"


Enviador::Enviador(Socket &peer, Queue<std::shared_ptr<MensajeServer>> *snapshots):skt(peer),snapshots_a_enviar(snapshots){

}


void Enviador::run()try{{
    is_alive = true;
    ServerProtocolo ptcl(skt);
    while(is_alive){
        std::shared_ptr<MensajeServer> msg = snapshots_a_enviar->pop();
        if(msg->get_tipo() == COMANDO::CMD_ENVIAR_SNAPSHOT){
            // printf("Se intenta enviar un snapshot\n");
            std::shared_ptr<MensajeSnapshotServer> msg_serv = std::dynamic_pointer_cast<MensajeSnapshotServer>(msg);
            std::shared_ptr<Snapshot> snap = msg_serv->get_snap();
            ptcl.enviar_snapshot(snap);
            // printf("Se termina de enviar un snapshot\n");
        }
        
        if(msg->get_tipo() == COMANDO::CMD_LISTAR_PARTIDAS){
            std::shared_ptr<MensajeListarPartidas> listar = std::dynamic_pointer_cast<MensajeListarPartidas>(msg);
            // printf("En el enviador se estan por mandar partidas\n");
            ptcl.enviar_partidas(listar->get_lista());
        }
        if(msg->get_tipo() == COMANDO::CMD_EMPEZAR_PARTIDA){
            // printf("Se envia mensaje de que la partida empezo\n");
            ptcl.check_partida_empezada();
        }
        if(msg->get_tipo() == COMANDO::CMD_HANDSHAKE){
            std::shared_ptr<MensajeHandshakeServer> hand = std::dynamic_pointer_cast<MensajeHandshakeServer>(msg);
            // printf("Se intenta enviar el handshake\n");
            ptcl.enviar_handshake(hand->get_gusanos_por_player_(),hand->get_snap());
        }
        
        if(msg->get_tipo() == COMANDO::CMD_LISTAR_MAPAS){
            
            std::shared_ptr<MensajeListarMapas> listar = std::dynamic_pointer_cast<MensajeListarMapas>(msg);
            if(!msg){
                printf("asdasdasd\n");
            }
            ptcl.enviar_mapas(listar->get_lista());
        }
        
    }
}}catch(const ClosedSocket& e){
        // printf("El cliente se desconecto\n");
        is_alive = false;
}catch(const ClosedQueue& e){
    is_alive = false;
}
