#ifndef WORM_H
#define WORM_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "../../common/worm_states.h"
#include "../../common/armas.h"
#include "./collision_categories.h"
#include "./armas/coleccion_armas.h"
#include "./proyectiles/projectile.h"
#include "./colisionable.h"

#include <vector>
#include <queue>

enum directions {
    RIGHT = 0,
    LEFT = 1,
};

#define MAX_VIDA 150

#define STATUS_MOVING 1
#define STATUS_IDLE 0

#define BOX_WIDTH 0.5f
#define BOX_HEIGHT 0.5f

#define WORM_DENSITY 0.2f
#define WORM_FRICTION 0.8f
#define WORM_RESTITUTION 0.5f
#define WORM_RESTITUTION_THRESHOLD 3.5f

#define MOVING_SPEED 0.7f
#define SUPER_SPEED 3.0f

#define FORWARD_JUMP_STEPS 38
#define BACKWARD_JUMP_STEPS 58

#define SUPER_FORWARD_JUMP_STEPS 58
#define SUPER_BACKWARD_JUMP_STEPS 78

#define FORWARD_JUMP_IMPULSE_MULTIPLIER 3.25
#define BACKWARD_JUMP_IMPULSE_MULTIPLIER 5

#define SUPER_FORWARD_JUMP_IMPULSE_MULTIPLIER 5
#define SUPER_BACKWARD_JUMP_IMPULSE_MULTIPLIER 7

#define FORWARD_JUMP_X_VELOCITY 1.62
#define BACKWARD_JUMP_X_VELOCITY 0.2

#define SUPER_FORWARD_JUMP_X_VELOCITY 4
#define SUPER_BACKWARD_JUMP_X_VELOCITY 1

class ColeccionArmas;

class Worm : public Colisionable {
private:
    b2Body* body;
    std::unique_ptr<ColeccionArmas> coleccionArmas;
    std::shared_ptr<Arma> armaActual;
    /* info de snapshot */
    int facingDirection;
    uint8_t status;
    uint32_t id;
    float angulo_disparo;
    int hitPoints;
    /* info tecnica */
    int maxHealth;
    int numBeamContacts;
    float initialHeight;
    float finalHeight;
    bool airborne;
    bool moving;
    bool esta_apuntando_para_arriba;
    bool apuntando;
    bool tomoDmgEsteTurno;
    float x_target;
    float y_target;
    float dead_posiiton_x;
    float dead_position_y;
    float dead_position_angle;
    bool pudo_cambiar_de_arma;
    bool super_velocidad;
    bool super_salto;

public:
    int jumpSteps;
    std::queue<SoundTypes> sounds;

    Worm(b2World& world, int hitPoints, int direction, float x_pos, float y_pos, uint32_t id);

    /* Movimiento */

    void StartMovement(int dir);

    void Move();

    void Stop();

    void JumpForward();

    void JumpBackward();

    void cambiar_direccion(uint8_t dir);

    /* Eventos */

    void startGroundContact();

    void endGroundContact();

    void startWaterContact();

    void takeDamage(int damage);

    void heal(int hit_points);

    void reload_weapons();

    void kill();

    void detener_acciones();

    /* Queries */

    bool isMoving();

    bool isAirborne();

    bool isDead();

    bool esta_apuntando();

    bool esta_cargando_arma();

    bool esta_quieto();

    bool tomo_dmg_este_turno();

    /* Combate / Setters */

    void cambiar_arma(uint8_t tipo_arma);

    void iniciar_carga();

    void cargar_arma();
    
    bool usar_arma(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id);

    void esta_apuntando_para(bool dir);

    void resetear_dmg();

    void incrementar_angulo_en(float inc);

    void set_target(float x, float y);

    void set_grenade_timer(int seconds);

    void parar_angulo();

    bool using_teleportacion();

    bool using_ataque_aereo();

    bool using_timer();

    void aumentar_vida(int vida);

    float get_timer();

    std::vector<float> posicion_marcada();

    /* Getters */

    std::vector<float> GetPosition();

    int get_facing_direction();

    uint8_t get_status();

    uint32_t get_id();

    float get_angulo();

    float get_aiming_angle();

    uint8_t get_vida();

    std::vector<std::pair<int,int>> get_municiones();

    uint16_t get_carga_actual();

    void reducir_vida();
    void super_velocidad_gusano();
    void super_salto_gusano();

    bool get_pudo_cambiar_de_arma();
};

#endif
