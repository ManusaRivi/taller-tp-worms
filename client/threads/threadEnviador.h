#ifndef _ENVIADOR
#define _ENVIADOR
#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../../common/queue.h"
#include "../snapshot.h"
#include "../comando.h"
#include "../protocolo/protocoloCliente.h"

struct Enviador:public Thread{

    Socket &skt;
    std::atomic<bool> is_alive;
    uint8_t id;
    Queue<Comando> &comandos_a_enviar;

    Enviador(Socket &peer, Queue<Comando> &queue_comandos);

    void run() override;

    bool is_dead();


};

#endif