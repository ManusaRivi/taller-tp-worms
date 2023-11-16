#ifndef _ENVIADOR
#define _ENVIADOR
#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../../common/queue.h"
#include "../game/comunicacion/snapshot.h"
#include "../comandos/comando.h"
#include "../protocolo/protocoloCliente.h"

struct Enviador:public Thread{

    Socket &skt;
    std::atomic<bool> is_alive;
    uint8_t id;
    Queue<std::shared_ptr<Mensaje>> &comandos_a_enviar;

    Enviador(Socket &peer, Queue<std::shared_ptr<Mensaje>> &queue_comandos);

    void run() override;

    bool is_dead();

    


};

#endif