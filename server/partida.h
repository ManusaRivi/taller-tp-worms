#ifndef _PARTIDA
#define _PARTIDA

#include "../common/queue.h"
#include "comandos/comando.h"
#include "../common/thread.h"
#include "juego/mapa.h"
#include "monitorBroadcaster.h"
#include <SDL2pp/SDL2pp.hh>

class Partida:public Thread{

    private:
    Queue<std::shared_ptr<Comando>> acciones_a_realizar;
    Mapa* mapa;
    BroadCaster broadcaster;
    uint32_t id_partida;
    std::string nombre_partida;
    std::vector<uint8_t> posibles_id_gusanos;
    std::map<uint32_t,std::vector<uint32_t>> id_gusanos_por_player;
    std::map<uint32_t,uint32_t> id_player_por_gusano;
    std::mutex lck;
    std::atomic<bool> is_alive;


    public:
    Partida(uint32_t id_partida, std::string nombre, Mapa* mapa);
    void run() override;
    std::string get_nombre();
    void add_queue(Queue<Mensaje>* snapshots);
    Queue<std::shared_ptr<Comando>>& get_queue();

    Snapshot generar_snapshot(float tiempo_turno, uint32_t id_gusano_current_turn);

    void remover_player(Queue<Mensaje>* snapshots);
    
    void kill();

    

    
    private:
    void enviar_primer_snapshot();

    uint32_t proximo_turno(uint32_t turno_actual);

};

#endif
