#include "../common/queue.h"
#include "comandos/comando.h"
#include "../common/thread.h"
#include "juego/mapa.h"
#include "monitorBroadcaster.h"
#include "comandos/comando_movimiento.h"

struct Partida{

    Queue<std::shared_ptr<Comando>> &acciones_a_realizar;
    Mapa mapa;
    BroadCaster &broadcaster;

    Partida(Queue<std::shared_ptr<Comando>> &acciones, BroadCaster &caster);

    void run();

    Snapshot generar_snapshot();

};
