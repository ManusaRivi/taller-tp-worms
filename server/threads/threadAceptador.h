#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/queue.h"
#include "../Cliente.h"
#include "../../client/snapshot.h"
#include "../monitorBroadcaster.h"
#include "../lobby.h"

#include <list>


struct Aceptador:public Thread{

    Socket aceptador;
    std::list<Cliente*> clientes;
    bool is_open;
    BroadCaster &broadcaster;
    Queue<std::shared_ptr<Comando>> &acciones_a_realizar;
    Lobby &lobby;

    Aceptador(const char *host_name, BroadCaster &caster, Queue<std::shared_ptr<Comando>> &acciones,Lobby &lobby);

    void run() override;


};