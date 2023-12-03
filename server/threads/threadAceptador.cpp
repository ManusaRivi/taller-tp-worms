#include "threadAceptador.h"
#include <unistd.h>

Aceptador::Aceptador(const char* hostname):aceptador(hostname),
                                            lobby(mapas)
                                            {
    // std::cout << "Se crea el aceptador" << std::endl;
}


void Aceptador::run() try{{



   // Sacar el id y poner dentro de la partida
    is_alive = keep_talking = true;
    while(keep_talking){
        Socket client_skt = this->aceptador.accept();
        // std::cout << "Se acepto un socket" << std::endl;

        
        Cliente *clte = new Cliente(client_skt,lobby);
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
    lobby.kill();
    this->keep_talking = false;
    aceptador.shutdown(2);
    aceptador.close();
}