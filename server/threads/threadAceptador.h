#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../Cliente.h"

#include <list>


struct Aceptador:public Thread{

    Socket aceptador;
    std::list<Cliente*> clientes;
    bool is_open;

    Aceptador(const char *host_name);

    void run() override;


};