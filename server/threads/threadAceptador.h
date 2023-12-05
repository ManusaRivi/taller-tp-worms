#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/queue.h"
#include "../Cliente.h"
#include "../snapshots/snapshot.h"
#include "../monitorBroadcaster.h"
#include "../lobby.h"

#include <list>


class Aceptador:public Thread{

    private:
    Socket aceptador;
    MapContainer mapas;
    std::list<Cliente*> clientes;
    std::atomic<bool> is_alive;
    std::atomic<bool> keep_talking;
    Lobby lobby;

    public:
    Aceptador(const char *host_name);
    void run() override;
    void shutdown();

    private:
    void kill();
    void reap_dead();
};
