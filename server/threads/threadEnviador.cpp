#include "threadEnviador.h"


Enviador::Enviador(Socket &peer, uint8_t _id, Queue<Mensaje> *snapshots):skt(peer), id(_id),snapshots_a_enviar(snapshots){

}


void Enviador::run(){
    bool was_closed = false;
    ServerProtocolo ptcl(skt);
    while(!was_closed){
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
        
    }
}
