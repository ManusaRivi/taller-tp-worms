#include "threadEnviador.h"


Enviador::Enviador(Socket &peer, Queue<Comando> &queue_comandos):skt(peer),comandos_a_enviar(queue_comandos){

}

void Enviador::run(){
    bool was_closed = false;
    Protocolo ptcl(skt);
    while(!was_closed){
        Comando cmd = comandos_a_enviar.pop();
        ptcl.enviar_comando(cmd);
    }
}