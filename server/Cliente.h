#include "threads/threadRecibidor.h"
#include "threads/threadEnviador.h"
#include "monitorBroadcaster.h"
#include "lobby.h"

struct Cliente{

    Socket skt;

    Recibidor *recibidor;
    Enviador *enviador;


    Queue<Mensaje>* snapshots_a_enviar;
    Lobby &lobby;

    Cliente(Socket &peer, Queue<Mensaje>* caster, Queue<std::shared_ptr<Comando>> &acciones_a_realizar,Lobby &lobby);

    void start();

    bool is_dead();

    void join();

    void kill();

    ~Cliente();
    

};