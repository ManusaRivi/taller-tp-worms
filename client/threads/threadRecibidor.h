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
    Queue<std::shared_ptr<MensajeCliente>> &queue_comandos;
    Recibidor(Socket &peer, Queue<std::shared_ptr<MensajeCliente>> &acciones,Queue<std::shared_ptr<MensajeCliente>> &queue_comandos);

    void run() override;

    bool is_dead();

    void kill();

};

#endif