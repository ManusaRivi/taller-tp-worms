#include "threads/threadAceptador.h"
#include "monitorBroadcaster.h"
#include "partida.h"
#include "server.h"

int main(int argc, char* argv[]){

    if (argc < 2 || argc > 3) {
        throw std::runtime_error("Los parametros ingresados son incorrectos.\n");
    }

    Aceptador skt(argv[1]);
    skt.start();

    ServerMain srvr (argc, argv);

    srvr.empezar_server();
    skt.shutdown();
    skt.join();
    
    return 0;
}
