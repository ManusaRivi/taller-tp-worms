#ifndef _CONTAINER
#define _CONTAINER
#include "threadRecibidor.h"
#include "threadEnviador.h"

struct containerThreads{

    Socket skt;
    Enviador enviador;
    Recibidor recibidor;

    containerThreads(Socket &peer,Queue<std::shared_ptr<Mensaje>> &snapthos_a_render,Queue<std::shared_ptr<Mensaje>> &queue_comandos);

    void start();

    void join();

    ~containerThreads();

};

#endif