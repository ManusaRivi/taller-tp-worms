#include "client.h"
#include "game.h"
#include "login.h"
#include "pocsdl.h"

Client::Client(int argc, char** argv, const char* serv_name, const char* port) : login(argc, argv), skt(serv_name,port), protocol(skt) {}

int Client::iniciar()
{
    this->login.start();

    //Deberia obtenerse el servname y el puerto del login
    //y crear el protocolo con eso, no ser un atributo del cliente

    //Game game(protocol);
    //return game.run();
    SDLPoc poc(protocol);
    return poc.run();
}