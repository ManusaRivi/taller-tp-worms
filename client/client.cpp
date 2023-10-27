#include "client.h"
#include "pocsdl.h"
#include "login.h"

Client::Client(int argc, char** argv) : login(argc, argv) {}

int Client::iniciar()
{
    //ProtocoloCliente ptcl = menu.begin();
    //O algo asi, para que abra el menu, se ingresen los datos del server
    //Cierre el menu y devuleva el protocolo

    this->login.start();

    //Game game(ptcl);
    //game.begin();

    SDLPoc poc;
    return poc.run();
}