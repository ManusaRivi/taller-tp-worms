#ifndef _RECIBIDOR
#define _RECIBIDOR

#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../../common/queue.h"
#include "../protocolo/protocoloServer.h"
#include "../lobby.h"


struct Lobby;
struct Recibidor:public Thread{


    Socket &skt;
    std::atomic<bool> is_alive;
    Queue<std::shared_ptr<Comando>> &acciones_a_realizar;
    uint8_t id;
    Queue<Mensaje>* snapshots;
    uint32_t id_partida;
    Lobby &lobby;
    uint8_t id_gusano;

    Recibidor(Socket &peer, Queue<std::shared_ptr<Comando>> &acciones, uint8_t id,Queue<Mensaje>* snapshots,Lobby &lobby);

    void run() override;

    bool is_dead();

};

#endif