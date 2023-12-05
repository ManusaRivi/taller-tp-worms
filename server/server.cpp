#include "server.h"
#include <string>
#include <iostream>

#include "juego/game_config.h"

ServerMain::ServerMain(int argc, char* argv[]) {
    if (argc == 3) {
        GameConfig& config = GameConfig::getInstance(argv[2]);
        (void)config;
    }
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