#include "client.h"


Client::Client(int argc, char** argv) : skt(nullptr), login(argc, argv, this->skt) {}

Client::~Client() {
    delete this->skt;
}

int Client::iniciar() {

    try {
        this->login.start();

        Queue<std::shared_ptr<MensajeCliente>> queue_comandos;
        Queue<std::shared_ptr<MensajeCliente>> queue_snapshots;

        

        this->skt = this->login.getSocket();

        if (this->skt == nullptr) {
            return 0;
        }

        
        containerThreads container(*this->skt, queue_snapshots, queue_comandos);

        
        container.start();
        
        Game game(queue_snapshots,queue_comandos);
        game.run();
        container.join();

        
        return 0;
        
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
	    return 1;
    }

}
