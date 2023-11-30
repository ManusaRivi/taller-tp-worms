#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_SEGUNDOS_POR_TURNO 60
#define FRAME_RATE 30.0f

enum GameStates {
    TURN,
    BONUS_TURN,
    WAITING
};

class TurnManager{

    std::map<uint32_t,std::vector<uint32_t>> id_gusanos_por_player;
    std::map<uint32_t,uint32_t> id_player_por_gusano;

    uint32_t cantidad_gusanos;
    uint32_t id_player_actual;
    uint32_t id_gusano_actual;

    uint32_t gusano_turno_anterior;
    int cantidad_players;

    GameStates state;

    uint8_t turn_timer;
    uint8_t bonus_turn_timer;

    bool acaba_de_pasar_turno;

    public:
    TurnManager();
    void cargar_cantidad_gusanos(uint32_t cantidad_gusanos);
    std::map<uint32_t, std::vector<uint32_t>> repartir_turnos(uint32_t cantidad_players);
    std::pair<bool,uint32_t> avanzar_tiempo(uint32_t iteracion);

    uint32_t get_player_actual();
    uint32_t get_gusano_actual();
    bool acaba_de_cambiar_turno();
    void deleteWorm(int idx);
    uint32_t getNextWorm(uint32_t id_player) const;
    uint32_t get_equipo(uint32_t id);
    bool checkOnePlayerRemains();
    GameStates get_state();
    void activar_bonus_turn();
    void terminar_espera();
};
