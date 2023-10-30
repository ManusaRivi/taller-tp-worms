#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/queue.h"
#include "../Cliente.h"
#include "../../client/snapshot.h"
#include "../monitorBroadcaster.h"

#include <list>


struct Aceptador:public Thread{

    Socket aceptador;
    std::list<Cliente*> clientes;
    bool is_open;
    BroadCaster &broadcaster;
    Queue<Comando> &acciones_a_realizar;

    Aceptador(const char *host_name, BroadCaster &caster, Queue<Comando> &acciones);

    void run() override;


};