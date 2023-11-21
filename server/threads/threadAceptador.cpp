#include "threadAceptador.h"
#include <unistd.h>

Aceptador::Aceptador(const char* hostname, BroadCaster &caster, Queue<std::shared_ptr<Comando>> &accion,Lobby &lobby_):aceptador(hostname), 
                                                                                                                    broadcaster(caster),
                                                                                                                    acciones_a_realizar(accion),
                                                                                                                    lobby(lobby_){
    // std::cout << "Se crea el aceptador" << std::endl;
}


void Aceptador::run() try{{


   // Sacar el id y poner dentro de la partida

    while(true){
        Socket client_skt = this->aceptador.accept();
        // std::cout << "Se acepto un socket" << std::endl;
        Queue<Mensaje> *queue_enviador = new Queue<Mensaje>;


        
        Cliente *clte = new Cliente(client_skt,queue_enviador,acciones_a_realizar,lobby);
        clte->start();
        //broadcaster.add_queue(queue_enviador);
        clientes.push_back(clte);
        }


}}
catch(const std::exception &error){
    kill();
    return;
}

void Aceptador::reap_dead() {

    clientes.remove_if([](Cliente* c) {
        if (c->is_dead()) {
            c->join();
            delete c;
            return true;
        }
        return false;
    });
}

void Aceptador::kill() {
    for (auto& c: clientes) {
        c->kill();
        c->join();
        delete c;
    }
    clientes.clear();
}

void Aceptador::shutdown(){
    this->is_open = false;
    aceptador.shutdown(2);
    aceptador.close();
}