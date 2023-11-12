#include "threadEnviador.h"


Enviador::Enviador(Socket &peer, Queue<Mensaje> &queue_comandos):skt(peer),comandos_a_enviar(queue_comandos){

}

void Enviador::run(){
    bool was_closed = false;
    ClienteProtocolo ptcl(skt);
    while(!was_closed){
        Mensaje cmd = comandos_a_enviar.pop();
        if (cmd.tipo_comando == COMANDO::CMD_ACCION_JUGADOR){
            std::shared_ptr<Comando> accion = cmd.cmd;
            if(!accion){
                continue;
            }
            accion.get()->enviar_accion(ptcl);
        }
        if(cmd.tipo_comando == COMANDO::CMD_CREAR_PARTIDA){
            ptcl.crear_partida(cmd.nombre_mapa);
        }
        if(cmd.tipo_comando == COMANDO::CMD_EMPEZAR_PARTIDA){
            ptcl.empezar_partida();
        }
        if(cmd.tipo_comando == COMANDO::CMD_HANDSHAKE){
            printf("Se quiere enviar un handshake\n");
            ptcl.enviar_handshake(cmd.id_player,cmd.id_gusanos);
        }
        
    }
}
