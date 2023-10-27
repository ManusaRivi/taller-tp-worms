#include "threadAceptador.h"
#include <unistd.h>

Aceptador::Aceptador(const char* hostname):aceptador(hostname){
    std::cout << "Se crea el aceptador" << std::endl;
}


void Aceptador::run(){
    Socket client_skt = this->aceptador.accept();

    std::cout << "Se acepto un socket" << std::endl;
    Cliente *clte = new Cliente(client_skt);
    clte->start();

    while(true){
        sleep(5);
        if (clte->is_dead()){
            std::cout << "El cliente esta muerto i se joinea" << std::endl;
            break;
        }
    }
    clte->join();
}
