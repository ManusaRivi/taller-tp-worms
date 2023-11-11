//#include "poc.h"
#include "threads/threadAceptador.h"
#include "monitorBroadcaster.h"
#include "partida.h"

int main(int argc, char* argv[]) {

    const char* name = "1568";
    BroadCaster broadcaster;
    Queue<std::shared_ptr<Comando>> acciones_a_realizar;
    Lobby lobby;
    Aceptador skt(name,broadcaster,acciones_a_realizar,lobby);
    skt.start();
    lobby.start_lobby();

    //Partida partida;
    //partida.run();
    //Box2dPoC poc;
    //poc.run();
    skt.join();
    return 0;
}