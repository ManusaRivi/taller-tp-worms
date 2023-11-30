#include "threadAceptador.h"
#include <unistd.h>

Aceptador::Aceptador(const char* hostname, Queue<std::shared_ptr<Comando>> &accion,Lobby &lobby_):aceptador(hostname), 
                                                                                                                    acciones_a_realizar(accion),
                                                                                                                    lobby(lobby_){
    // std::cout << "Se crea el aceptador" << std::endl;
}


void Aceptador::run() try{{


   // Sacar el id y poner dentro de la partida
    is_alive = keep_talking = true;
    while(keep_talking){
        Socket client_skt = this->aceptador.accept();
        // std::cout << "Se acepto un socket" << std::endl;

        
        Cliente *clte = new Cliente(client_skt,acciones_a_realizar,lobby);
        clte->start();
        reap_dead();
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
    this->keep_talking = false;
    aceptador.shutdown(2);
    aceptador.close();
}