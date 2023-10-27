#include "client.h"
#include "pocsdl.h"
#include "login.h"

Client::Client(int argc, char** argv, const char* serv_name, const char* port) : login(argc, argv), skt(serv_name,port), protocol(skt) {}

int Client::iniciar()
{
    //ProtocoloCliente ptcl = menu.begin();
    //O algo asi, para que abra el menu, se ingresen los datos del server
    //Cierre el menu y devuleva el protocolo

    this->login.start();

    //Game game(ptcl);
    //game.begin();

    SDLPoc poc(protocol);
    return poc.run();
}