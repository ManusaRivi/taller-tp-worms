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

#define STATUS_MOVING 1
#define STATUS_IDLE 0

#define BOX_WIDTH 0.5f
#define BOX_HEIGHT 0.5f

#define WORM_DENSITY 0.2f
#define WORM_FRICTION 0.8f
#define WORM_RESTITUTION 0.5f

#define MOVING_SPEED 0.335f

#define FORWARD_JUMP_STEPS 38
#define BACKWARD_JUMP_STEPS 58

#define FORWARD_JUMP_IMPULSE_MULTIPLIER 3.25
#define BACKWARD_JUMP_IMPULSE_MULTIPLIER 5

#define FORWARD_JUMP_X_VELOCITY 1.62
#define BACKWARD_JUMP_X_VELOCITY 0.2

class ColeccionArmas;

class Worm : public Colisionable {
private:
    b2Body* body;
    ColeccionArmas* coleccionArmas;
    Arma* armaActual;
    bool moving;
    int facingDirection;
    bool airborne;
    uint8_t hitPoints;
    float initialHeight;
    float finalHeight;

public:
    int jumpSteps;
    uint32_t id;
    uint8_t status;
    float angulo;
    float angulo_disparo;
    bool esta_apuntando_para_arriba;
    bool apuntando;
    std::queue<SoundTypes> sounds;

    Worm(b2World& world, int hitPoints, int direction, float x_pos, float y_pos, uint32_t id);
    virtual bodyType identificar() override;
    void StartMovement(int dir);
    void Move();
    void Stop();
    void JumpForward();
    void JumpBackward();
    void startGroundContact();
    void endGroundContact();
    bool isMoving();
    void startWaterContact();
    bool isAirborne();
    void takeDamage(int damage);
    std::vector<float> GetPosition();
    float GetAngle();
    bool isDead();
    void kill();
    
    void usar_arma(std::vector<Projectile*>& projectiles, uint32_t& entity_id);

    int get_facing_direction();

    uint32_t get_id();

    uint8_t get_status();

    float get_angulo();

    void cambiar_arma(uint8_t tipo_arma);

    void iniciar_carga();

    void cargar_arma();

    bool esta_cargando_arma();

    void esta_apuntando_para(bool dir);

    bool apuntando_para_arriba(bool dir);

    void incrementar_angulo_en(float inc);

    void set_grenade_timer(int seconds);

    bool esta_apuntando();

    void cambiar_angulo();

    void detener_acciones();

    float aiming_angle();

    void parar_angulo();

    uint8_t get_vida();

    void cambiar_direccion(uint8_t dir);
};

#endif
