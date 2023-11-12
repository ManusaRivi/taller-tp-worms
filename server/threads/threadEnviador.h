#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../../common/queue.h"
#include "../protocolo/protocoloServer.h"
#include "../snapshot.h"


struct Enviador:public Thread{

    Socket &skt;
    std::atomic<bool> is_alive;
    uint32_t id;
    Queue<Mensaje> *snapshots_a_enviar;

    Enviador(Socket &peer, Queue<Mensaje>* snapshots);

    void run() override;

    bool is_dead();


};