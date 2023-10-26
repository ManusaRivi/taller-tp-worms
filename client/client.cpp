#include "client.h"

Client::Client(){}

int Client::iniciar(){
    ProtocoloCliente ptcl = menu.begin();
    //O algo asi, para que abra el menu, se ingresen los datos del server
    //Cierre el menu y devuleva el protocolo



    Game game(ptcl);
    game.begin();
}