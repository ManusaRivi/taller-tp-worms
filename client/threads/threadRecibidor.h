#ifndef _RECIBIODR
#define _RECIBIDOR
#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../../common/queue.h"
#include "../game/comunicacion/snapshot.h"
#include "../protocolo/protocoloCliente.h"
#include "../comandos/mensaje.h"


struct Recibidor:public Thread{


    Socket &skt;
    std::atomic<bool> is_alive;
    Queue<std::shared_ptr<MensajeCliente>> &snapshots_a_render;
    Recibidor(Socket &peer, Queue<std::shared_ptr<MensajeCliente>> &acciones);

    void run() override;

    bool is_dead();

};

#endif