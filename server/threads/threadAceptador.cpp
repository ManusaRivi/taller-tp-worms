#include "threadAceptador.h"
#include <unistd.h>

Aceptador::Aceptador(const char* hostname, BroadCaster &caster, Queue<std::shared_ptr<Comando>> &accion,Lobby &lobby_):aceptador(hostname), 
                                                                                                                    broadcaster(caster),
                                                                                                                    acciones_a_realizar(accion),
                                                                                                                    lobby(lobby_){
    std::cout << "Se crea el aceptador" << std::endl;
}


void Aceptador::run(){

    uint8_t id = 0;

   // Sacar el id y poner dentro de la partida

    while(true){
        Socket client_skt = this->aceptador.accept();
        std::cout << "Se acepto un socket" << std::endl;
        Queue<Mensaje> *queue_enviador = new Queue<Mensaje>;
        
        Cliente *clte = new Cliente(client_skt,id,queue_enviador,acciones_a_realizar,lobby);
        clte->start();
        //broadcaster.add_queue(queue_enviador);
        clientes.push_back(clte);
        id++;
    }
    
}
