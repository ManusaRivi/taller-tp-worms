//#include "poc.h"
#include "threads/threadAceptador.h"
#include "monitorBroadcaster.h"
#include "partida.h"
#include "server.h"

int main(int argc, char* argv[]){

    const char* name = "1626";

    Aceptador skt(name);
    printf("Se abre un server con puerto : %s\n",name);
    skt.start();

    ServerMain srvr;

    srvr.empezar_server();
    skt.shutdown();
    skt.join();
    
    printf("Se cierra el server correctamente\n");
    return 0;
}