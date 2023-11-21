#include "server.h"
#include <string>
#include <iostream>


ServerMain::ServerMain(){

}


void ServerMain::empezar_server(){

    bool comando_cerrar = false;
    while (!comando_cerrar) {
        std::string comando;
        std::cin >> comando;

        if (comando == "q") {
            comando_cerrar = true;
            return;
        }

    }

}