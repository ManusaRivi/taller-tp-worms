#ifndef _PARTIDA
#define _PARTIDA

#include "../common/queue.h"
#include "comandos/comando.h"
#include "../common/thread.h"
#include "juego/mapa.h"
#include "monitorBroadcaster.h"
#include <SDL2pp/SDL2pp.hh>
#include "snapshots/snapshot_partida.h"
#include "snapshots/snapshot_handshake.h"

class Partida:public Thread{

    private:
    Queue<std::shared_ptr<Comando>> acciones_a_realizar;
    Mapa mapa;
    BroadCaster broadcaster;
    uint32_t id_partida;
    std::string nombre_partida;
    std::vector<uint8_t> posibles_id_gusanos;
    std::map<uint32_t,std::vector<uint32_t>> id_gusanos_por_player;
    std::map<uint32_t,uint32_t> id_player_por_gusano;
    std::mutex lck;
    std::atomic<bool> is_alive;
    std::atomic<bool> partida_empezada;
    std::atomic<bool> partida_terminada;
    FactoryMensajesServer mensajes;


    public:
    Partida(uint32_t id_partida, std::string nombre, std::string archivo_yaml);
    void run() override;
    std::string get_nombre();
    void add_queue(Queue<std::shared_ptr<MensajeServer>>* snapshots);
    Queue<std::shared_ptr<Comando>>& get_queue();

    std::shared_ptr<Snapshot> generar_snapshot(int iteracion);

    void remover_player(Queue<std::shared_ptr<MensajeServer>>* snapshots);
    
    void kill();

    bool partida_accesible();

    bool terminada();


    

    
    private:
    void enviar_primer_snapshot();
    void comenzar_partida();
    void enviar_termino_partida();


};

#endif
