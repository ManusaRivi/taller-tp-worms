#include "../common/queue.h"
#include "comandos/comando.h"
#include "../common/thread.h"
#include "juego/mapa.h"
#include "monitorBroadcaster.h"
#include "comandos/comando_movimiento.h"

struct Partida{

    Queue<Comando> &acciones_a_realizar;
    Mapa mapa;
    BroadCaster &broadcaster;

    Partida(Queue<Comando> &acciones, BroadCaster &caster);

    void run();

};
