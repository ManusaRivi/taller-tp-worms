#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../../common/queue.h"
#include "../protocolo/protocoloServer.h"
#include "../snapshots/snapshot.h"
#include "../comandos/mensajes/factory_mensajes.h"


struct Enviador:public Thread{

    Socket &skt;
    std::atomic<bool> is_alive;
    uint32_t id;
    Queue<std::shared_ptr<MensajeServer>> *snapshots_a_enviar;

    Enviador(Socket &peer, Queue<std::shared_ptr<MensajeServer>>* snapshots);

    void run() override;

    bool is_dead();


};