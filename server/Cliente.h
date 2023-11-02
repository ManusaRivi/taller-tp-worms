#include "threads/threadRecibidor.h"
#include "threads/threadEnviador.h"
#include "monitorBroadcaster.h"

struct Cliente{

    Socket skt;

    Recibidor *recibidor;
    Enviador *enviador;

    uint8_t id;

    Queue<Snapshot>* snapshots_a_enviar;

    Cliente(Socket &peer, uint8_t identificador, Queue<Snapshot>* caster, Queue<std::shared_ptr<Comando>> &acciones_a_realizar);

    void start();

    bool is_dead();

    void join();

};