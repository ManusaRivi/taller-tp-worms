#include "threadEnviador.h"


Enviador::Enviador(Socket &peer, Queue<std::shared_ptr<Comando>> &queue_comandos):skt(peer),comandos_a_enviar(queue_comandos){

}

void Enviador::run(){
    bool was_closed = false;
    Protocolo ptcl(skt);
    while(!was_closed){
        std::shared_ptr<Comando> cmd = comandos_a_enviar.pop();
        if (!cmd){
            continue;
        }
        cmd.get()->enviar_accion(ptcl);
    }
}
