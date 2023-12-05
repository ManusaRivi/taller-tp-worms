//#include "poc.h"
#include "threads/threadAceptador.h"
#include "monitorBroadcaster.h"
#include "partida.h"
#include "server.h"

int main(int argc, char* argv[]){

    if (argc < 2 || argc > 3) {
        throw std::runtime_error("Los parametros ingresados son incorrectos.\n");
    }

    Aceptador skt(argv[1]);
    printf("Se abre un server con puerto : %s\n", argv[1]);
    skt.start();

    ServerMain srvr (argc, argv);

    srvr.empezar_server();
    skt.shutdown();
    skt.join();
    
    printf("Se cierra el server correctamente\n");
    return 0;
}