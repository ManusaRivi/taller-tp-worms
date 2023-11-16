//#include "poc.h"
#include "threads/threadAceptador.h"
#include "monitorBroadcaster.h"
#include "partida.h"

int main(int argc, char* argv[]) {

    const char* name = "1583";
    BroadCaster broadcaster;
    Queue<std::shared_ptr<Comando>> acciones_a_realizar;
    Lobby lobby;
    Aceptador skt(name,broadcaster,acciones_a_realizar,lobby);
    skt.start();
    //lobby.start_lobby();

    bool comando_cerrar = false;
    while (!comando_cerrar) {
        std::string comando;
        std::cin >> comando;

        if (comando == "q") {
            comando_cerrar = true;
            break;
        }
}

    //Partida partida;
    //partida.run();
    //Box2dPoC poc;
    //poc.run();
    skt.join();
    return 0;
}