#include "threadEnviador.h"
#include "../comandos/mensajes/mensaje_handshake.h"
#include "../comandos/mensajes/mensaje_snapshot.h"
#include "../comandos/mensajes/mensaje_handshake_enviar.h"
#include "../comandos/mensajes/mensaje_accion_jugador.h"


Enviador::Enviador(Socket &peer, Queue<std::shared_ptr<MensajeCliente>> &queue_comandos):skt(peer),comandos_a_enviar(queue_comandos){

}

void Enviador::run()try{{
    bool was_closed = false;
    ClienteProtocolo ptcl(skt);
    while(!was_closed){
        std::shared_ptr<MensajeCliente> cmd = comandos_a_enviar.pop();
        if (cmd->get_tipo_comando() == COMANDO::CMD_ACCION_JUGADOR){
            std::shared_ptr<MensajeAccionJugador> accion =std::dynamic_pointer_cast<MensajeAccionJugador>(cmd);
            std::shared_ptr<ComandoCliente> comando = accion->get_accion();
            if(!accion){
                continue;
            }
            comando->enviar_accion(ptcl);
        }
        // if(cmd->get_tipo_comando() == COMANDO::CMD_CREAR_PARTIDA){
        //     ptcl.crear_partida(cmd->nombre_mapa,0);
        // }
        // if(cmd->get_tipo_comando() == COMANDO::CMD_EMPEZAR_PARTIDA){
        //     ptcl.empezar_partida();
        // }
        if(cmd && cmd->get_tipo_comando() == COMANDO::CMD_HANDSHAKE){
            printf("Se quiere enviar un handshake\n");
            std::shared_ptr<MensajeHandshake> hand = std::dynamic_pointer_cast<MensajeHandshake>(cmd);
            if(!hand){
                return;
            }
            printf("Se castea el pointer\n");
            ptcl.enviar_handshake(hand->get_id(),hand->get_gusanos());
            printf("Se envia el handshake\n");
        }
        
    }
}}
catch(const ClosedQueue& err){
    is_alive = false;
}
