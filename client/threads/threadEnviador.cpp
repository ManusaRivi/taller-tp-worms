#include "threadEnviador.h"


Enviador::Enviador(Socket &peer, Queue<std::shared_ptr<MensajeCliente>> &queue_comandos):skt(peer),comandos_a_enviar(queue_comandos){

}

void Enviador::run()try{{
    bool was_closed = false;
    ClienteProtocolo ptcl(skt);
    while(!was_closed){
        std::shared_ptr<MensajeCliente> cmd = comandos_a_enviar.pop();
        if (cmd->tipo_comando == COMANDO::CMD_ACCION_JUGADOR){
            std::shared_ptr<ComandoCliente> accion = cmd->cmd;
            if(!accion){
                continue;
            }
            accion->enviar_accion(ptcl);
        }
        if(cmd->tipo_comando == COMANDO::CMD_CREAR_PARTIDA){
            ptcl.crear_partida(cmd->nombre_mapa);
        }
        if(cmd->tipo_comando == COMANDO::CMD_EMPEZAR_PARTIDA){
            ptcl.empezar_partida();
        }
        if(cmd->tipo_comando == COMANDO::CMD_HANDSHAKE){
            printf("Se quiere enviar un handshake\n");
            ptcl.enviar_handshake(cmd->id_player,cmd->id_gusanos);
        }
        
    }
}}
catch(const ClosedQueue& err){
    is_alive = false;
}
