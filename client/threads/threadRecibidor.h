#ifndef _RECIBIODR
#define _RECIBIDOR
#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../../common/queue.h"
#include "../snapshot.h"
#include "../protocolo/protocoloCliente.h"


struct Recibidor:public Thread{


    Socket &skt;
    std::atomic<bool> is_alive;
    Queue<Snapshot> &snapshots_a_render;
    Recibidor(Socket &peer, Queue<Snapshot> &acciones);

    void run() override;

    bool is_dead();

};

#endif