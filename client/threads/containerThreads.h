#ifndef _CONTAINER
#define _CONTAINER
#include "threadRecibidor.h"
#include "threadEnviador.h"

struct containerThreads{

    Socket skt;
    Enviador *enviador;
    Recibidor *recibidor;

    containerThreads(Socket &peer,Queue<Snapshot> &snapthos_a_render,Queue<Comando> &queue_comandos);

    void start();

    void join();

    ~containerThreads();

};

#endif