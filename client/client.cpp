#include "client.h"
#include "game.h"
#include "login.h"
#include "pocsdl.h"


Client::Client(int argc, char** argv) : login(argc, argv) {}

int Client::iniciar() {

    try {
        this->login.start();

        //const std::string server = this->login.getServer();
        //const std::string port = this->login.getPort();

        const std::string server = "127.0.0.1";
        const std::string port = "8080";

        Queue<std::shared_ptr<Comando>> queue_comandos; //TODO: Cambiar a Unique ptr
        Queue<Snapshot> queue_snapshots;

        Socket skt(server.data(),port.data());

        containerThreads container(skt,queue_snapshots,queue_comandos);

        //Protocolo prot(server, port);
        container.start();
        Game game(queue_snapshots,queue_comandos);
        game.run();
        container.join();
        return 0;
        // SDLPoc poc(queue_snapshots,queue_comandos);
        // return poc.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
	    return 1;
    }

}