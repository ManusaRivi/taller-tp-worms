#include "threadEnviador.h"


Enviador::Enviador(Socket &peer, Queue<std::shared_ptr<MensajeServer>> *snapshots):skt(peer),snapshots_a_enviar(snapshots){

}


void Enviador::run()try{{
    is_alive = true;
    ServerProtocolo ptcl(skt);
    while(is_alive){
        std::shared_ptr<MensajeServer> msg = snapshots_a_enviar->pop();
        if(msg->get_tipo() == COMANDO::CMD_ENVIAR_SNAPSHOT){
            std::shared_ptr<MensajeSnapshotServer> msg_serv = std::dynamic_pointer_cast<MensajeSnapshotServer>(msg);
            std::shared_ptr<Snapshot> snap = msg_serv->get_snap();
            ptcl.enviar_snapshot(snap);
        }
        if(msg->get_tipo() == COMANDO::CMD_LISTAR_PARTIDAS){
            std::shared_ptr<MensajeListarPartidas> listar = std::dynamic_pointer_cast<MensajeListarPartidas>(msg);
            ptcl.enviar_partidas(listar->get_lista());
        }
        if(msg->get_tipo() == COMANDO::CMD_EMPEZAR_PARTIDA){
            ptcl.check_partida_empezada();
        }
        if(msg->get_tipo() == COMANDO::CMD_HANDSHAKE){
            std::shared_ptr<MensajeHandshakeServer> hand = std::dynamic_pointer_cast<MensajeHandshakeServer>(msg);
            ptcl.enviar_handshake(hand->get_gusanos_por_player_(),hand->get_snap());
        }
        if(msg->get_tipo() == COMANDO::CMD_LISTAR_MAPAS){
            std::shared_ptr<MensajeListarMapas> listar = std::dynamic_pointer_cast<MensajeListarMapas>(msg);
            ptcl.enviar_mapas(listar->get_lista());
        }
        if(msg->get_tipo() == COMANDO::CMD_ESTADO_UNIRSE){
            std::shared_ptr<MensajeEstadoUnirse> estado = std::dynamic_pointer_cast<MensajeEstadoUnirse>(msg);
            ptcl.enviar_estado_unirse(estado->get_state());
        }
        if(msg->get_tipo() == COMANDO::CMD_PARTIDA_TERMINO){
            std::shared_ptr<MensajePartidaTermino> estado = std::dynamic_pointer_cast<MensajePartidaTermino>(msg);
            ptcl.enviar_partida_termino(estado->get_equipo_ganador(),estado->fue_empate_());
        }
    }
}}catch(const ClosedSocket& e){
        is_alive = false;
}catch(const ClosedQueue& e){
    is_alive = false;
}
