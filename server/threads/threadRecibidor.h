#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../../common/queue.h"
#include "../protocolo/protocoloServer.h"


struct Recibidor:public Thread{


    Socket &skt;
    std::atomic<bool> is_alive;
    Queue<Comando> &acciones_a_realizar;
    uint8_t id;

    Recibidor(Socket &peer, Queue<Comando> &acciones, uint8_t id);

    void run() override;

    bool is_dead();

};