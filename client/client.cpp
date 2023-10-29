#include "client.h"
#include "game.h"
#include "login.h"
#include "pocsdl.h"

Client::Client(int argc, char** argv) : login(argc, argv) {}

int Client::iniciar() {

    try {
        this->login.start();

        const std::string server = this->login.getServer();
        const std::string port = this->login.getPort();

        Protocolo prot(server, port);

        //Game game(prot);
        //return game.run();
        SDLPoc poc(prot);
        return poc.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
	    return 1;
    }

}