//#include "poc.h"
#include "threads/threadAceptador.h"
#include "monitorBroadcaster.h"
#include "partida.h"

int main(int argc, char* argv[]) {

    const char* name = "1617";
    BroadCaster broadcaster;
    Queue<std::shared_ptr<Comando>> acciones_a_realizar;
    MapContainer mapas;
    Lobby lobby(mapas);
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
    printf("Se le hace kill al lobby\n");
    lobby.kill();
    printf("Se le hace shutdown al socket\n");
    skt.shutdown();
    //MapContainer mapContainer;
    //Partida partida;
    //partida.run();
    //Box2dPoC poc;
    //poc.run();
    printf("Se le va a hacer join al socket\n");
    skt.join();
    printf("Se le hace join al socket\n");
    return 0;
}