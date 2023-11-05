#ifndef _CONTAINER
#define _CONTAINER
#include "threadRecibidor.h"
#include "threadEnviador.h"

struct containerThreads{

    Socket skt;
    Enviador *enviador;
    Recibidor *recibidor;

    containerThreads(Socket &peer,Queue<Mensaje> &snapthos_a_render,Queue<Mensaje> &queue_comandos);

    void start();

    void join();

    ~containerThreads();

};

#endif