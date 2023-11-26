//#include "poc.h"
#include "threads/threadAceptador.h"
#include "monitorBroadcaster.h"
#include "partida.h"
#include "server.h"

int main(int argc, char* argv[]) {

    const char* name = "1625";
    BroadCaster broadcaster;
    Queue<std::shared_ptr<Comando>> acciones_a_realizar;
    MapContainer mapas;
    Lobby lobby(mapas);
    Aceptador skt(name,broadcaster,acciones_a_realizar,lobby);
    printf("Se abre un server con puerto : %s\n",name);
    skt.start();

    ServerMain srvr;

    srvr.empezar_server();

    lobby.kill();
    skt.shutdown();
    //MapContainer mapContainer;
    //Partida partida;
    //partida.run();
    //Box2dPoC poc;
    //poc.run();
    skt.join();
    printf("Se cierra el server correctamente\n");
    return 0;
}