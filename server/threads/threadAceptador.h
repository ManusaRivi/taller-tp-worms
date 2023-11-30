#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/queue.h"
#include "../Cliente.h"
#include "../snapshot.h"
#include "../monitorBroadcaster.h"
#include "../lobby.h"

#include <list>


class Aceptador:public Thread{

    private:
    Socket aceptador;
    std::list<Cliente*> clientes;
    std::atomic<bool> is_alive;
    std::atomic<bool> keep_talking;
    Queue<std::shared_ptr<Comando>> &acciones_a_realizar;
    Lobby &lobby;

    public:
    Aceptador(const char *host_name, Queue<std::shared_ptr<Comando>> &acciones,Lobby &lobby);
    void run() override;
    void shutdown();


    private:
    void kill();
    void reap_dead();


};