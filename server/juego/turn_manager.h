#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <random>
#include "worm.h"
#include "../../common/queue.h"


#define MAX_SEGUNDOS_POR_TURNO 60
#define BONUS_SECONDS 3
#define FRAME_RATE 30.0f

enum GameStates {
    TURN,
    BONUS_TURN,
    WAITING
};

class TurnManager{

    std::map<uint32_t,std::vector<uint32_t>> id_gusanos_por_player;
    std::map<uint32_t,uint32_t> id_player_por_gusano;
    std::map<uint32_t, Queue<uint32_t>> queue_siguiente_gusano_por_player;

    uint32_t cantidad_gusanos;
    uint32_t id_player_actual;
    uint32_t id_gusano_actual;
    std::vector<uint32_t> players_eliminados;

    uint32_t gusano_turno_anterior;
    int cantidad_players;

    GameStates state;

    uint16_t turn_timer;
    uint16_t bonus_turn_timer;
    uint16_t waiting_timer;

    bool acaba_de_pasar_turno;

    public:
    TurnManager();
    void cargar_cantidad_gusanos(uint32_t cantidad_gusanos);
    std::map<uint32_t, std::vector<uint32_t>> repartir_turnos(uint32_t cantidad_players,std::vector<std::shared_ptr<Worm>>& vectorWorms);
    void avanzar_tiempo(uint32_t iteracion, std::vector<std::shared_ptr<Worm>>& vectorWorms, bool perdio_turno);

    bool es_gusano_actual(uint32_t idx);
    uint32_t get_player_actual();
    uint32_t get_gusano_actual();
    bool acaba_de_cambiar_turno();
    void deleteWorm(int idx);
    uint32_t getNextWorm(uint32_t id_player) const;
    uint32_t get_equipo(uint32_t id);
    bool checkOnePlayerRemains();
    GameStates get_state();
    void activar_bonus_turn();
    void terminar_espera(std::vector<std::shared_ptr<Worm>>& vectorWorms, bool& paso_de_turno);
    void pasar_turno_si_muerto(int idx,std::vector<std::shared_ptr<Worm>>& vectorWorms);
    uint32_t get_tiempo_actual();
    bool fue_empate();
    uint32_t equipo_ganador();
    private:
    void randomizar_queue_player();
    void turno_siguiente_player(std::vector<std::shared_ptr<Worm>>& vectorWorms);
    bool gusano_esta_vivo(uint32_t id,std::vector<std::shared_ptr<Worm>>& vectorWorms);
    void detener_gusano_actual(std::vector<std::shared_ptr<Worm>>& vectorWorms);
    void balance_de_fuerza(std::vector<std::shared_ptr<Worm>>& vectorWorms);
};
