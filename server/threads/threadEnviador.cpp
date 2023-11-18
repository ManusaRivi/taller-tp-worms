#include "threadEnviador.h"


Enviador::Enviador(Socket &peer, Queue<Mensaje> *snapshots):skt(peer),snapshots_a_enviar(snapshots){

}


void Enviador::run()try{{
    is_alive = true;
    ServerProtocolo ptcl(skt);
    while(is_alive){
        Mensaje msg = snapshots_a_enviar->pop();
        if(msg.tipo_comando == COMANDO::CMD_ENVIAR_SNAPSHOT){
            Snapshot snap = msg.snap;
            ptcl.enviar_snapshot(snap);
        }
        if(msg.tipo_comando == COMANDO::CMD_LISTAR_PARTIDAS){
            printf("En el enviador se estan por mandar partidas\n");
            ptcl.enviar_partidas(msg.lista_mapas);
        }
        if(msg.tipo_mensaje() == COMANDO::CMD_EMPEZAR_PARTIDA){
            printf("Se envia mensaje de que la partida empezo\n");
            ptcl.check_partida_empezada();
        }

        if(msg.tipo_mensaje() == COMANDO::CMD_HANDSHAKE){
            printf("Se envia un handshake\n");
            ptcl.enviar_handshake(msg.gusanos_por_player,msg.snap);
        }

        if(msg.tipo_mensaje() == COMANDO::CMD_LISTAR_MAPAS){
            printf("Se envia la lista de mapas");
            ptcl.enviar_mapas(msg.lista_mapas);
        }
        
    }
}}catch(const ClosedSocket& e){
        printf("El cliente se desconecto\n");
        is_alive = false;
        delete snapshots_a_enviar;
}catch(const ClosedQueue& e){
    is_alive = false;
}
