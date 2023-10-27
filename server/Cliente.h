#include "threads/threadRecibidor.h"

struct Cliente{

    Socket& skt;

    Recibidor *recibidor;

    Cliente(Socket &peer);

    void start();

    bool is_dead();

    void join();

};