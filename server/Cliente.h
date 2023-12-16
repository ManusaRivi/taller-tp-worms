#include "threads/threadRecibidor.h"
#include "threads/threadEnviador.h"
#include "monitorBroadcaster.h"
#include "lobby.h"

struct Cliente{

    Socket skt;

    Recibidor *recibidor;
    Enviador *enviador;


    Queue<std::shared_ptr<MensajeServer>>* snapshots_a_enviar;
    Lobby &lobby;

    Cliente(Socket &peer,Lobby &lobby);

    void start();

    bool is_dead();

    void join();

    void kill();

    ~Cliente();
    

};
