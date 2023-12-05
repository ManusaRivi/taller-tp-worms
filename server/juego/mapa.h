#ifndef MAPA_H
#define MAPA_H

#include "../../libs/box2d/include/box2d/box2d.h"

#include <yaml-cpp/yaml.h>
#include <vector>
#include <string>
#include <queue>
#include <cstdlib>
#include <random>

#include "./game_config.h"
#include "../worm_wrapper.h"
#include "../projectile_wrapper.h"
#include "../explosion_wrapper.h"
#include "../provisiones_wrapper.h"
#include "../../common/sound_types.h"
#include "../../common/provision_types.h"
#include "./worm.h"
#include "./beam.h"
#include "./proyectiles/projectile.h"
#include "./proyectiles/fragment.h"
#include "./proyectiles/grenade.h"
#include "./provisiones/provision.h"
#include "./provisiones/vida.h"
#include "./provisiones/municion.h"
#include "./provisiones/trampa.h"
#include "./water.h"
#include "./contact_listener.h"
#include "turn_manager.h"

#define	RAND_LIMIT 32767

#define MIN_WIND_SPEED 0.01f
#define MAX_WIND_SPEED 0.1f

#define MAX_PROVISIONS 2
#define PROVISION_HEIGHT 50.0f
#define MAX_PROVISION_X_POS 40
#define PROBABILDAD_DE_CREAR_PROVISIONES 0.20f

// Copyright (c) 2019 Erin Catto

class Mapa {
private:
    b2World world;
    ContactListener contactListener;

    const float timeStep = 1.0f / 30.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

    std::vector<std::shared_ptr<BeamServer>> vigas;
    std::vector<std::shared_ptr<Worm>> worms;
    std::vector<std::shared_ptr<Projectile>> projectiles;
    std::vector<std::shared_ptr<Provision>> provisiones;
    std::queue<ExplosionWrapper> explosions;
    std::queue<SoundTypes> sounds;
    Water water;

    float viento;

    std::string nombre;
    TurnManager turnManager;
    uint32_t identificador_entidades;

    void crear_provisiones();
    inline float RandomFloat(float lo, float hi) {
        float r = (float)(rand() & (RAND_LIMIT));
        r /= RAND_LIMIT;
        r = (hi - lo) * r + lo;
        return r;
    }
public:
    explicit Mapa(std::string map_filepath);
    void Load_Map_File(std::string filepath);
    void cambiar_viento();
    bool Step(int iteracion);
    /*
    * Setea la velocidad del gusano dado por idx, que es el
    * indice en el vector gusanos del gusano a mover.
    * Si dir es 0, se mueve a la derecha. Si es 1, a la izquierda.
    * */
    void MoveWorm(uint32_t id, int dir);
    /*
    * Setea la velocidad en x del gusano cuyo indice es idx a 0.
    * Mantiene la velocidad en y, para que si esta cayendo y se detiene,
    * siga cayendo con la misma velocidad hacia abajo.
    * */
    void StopWorm(uint32_t id);
    void JumpWormForward(uint32_t id);
    void JumpWormBackward(uint32_t id);

    void cambiar_direccion(uint32_t id, uint8_t dir);

    void cambiar_arma(uint32_t id, uint8_t tipo);

    void apuntar_para(uint32_t id,int);

    void cargar_arma(uint32_t id);

    void usar_arma(uint32_t id);

    void set_grenade_time(uint32_t id, int seconds);

    void set_target(uint32_t id, float x, float y);

    void detener_worm(uint32_t id);

    void detener_angulo(uint32_t id);

    std::map<uint32_t, std::vector<uint32_t>> repartir_ids(uint32_t cantidad_jugadores);

    bool checkOnePlayerRemains();
    
    uint32_t gusano_actual();

    std::string GetName();

    void esta_usando_armas_especiales(std::vector<std::pair<uint8_t,std::vector<float>>>& armas_especiales);

    void get_vigas(std::vector<std::vector<float>>& beam_vector);

    uint16_t gusanos_totales();

    void get_gusanos(std::vector<WormWrapper>& worm_vector);

    void get_projectiles(std::vector<ProjectileWrapper>& projectile_vector, uint32_t& apuntar_camara);

    void get_explosions(std::vector<ExplosionWrapper>& explosion_vector);

    void get_sounds(std::vector<SoundTypes>& sound_vector);

    void get_provisiones(std::vector<ProvisionWrapper>& provision_vector);
    
    void get_municiones_worm(std::vector<std::pair<int,int>>& municiones);

    uint32_t get_tiempo_turno_actual();

    uint16_t get_carga_actual();

    float get_viento_actual(bool& es_negativo);

    uint32_t cantidad_worms();

    void reducir_vida();

    uint32_t get_equipo_ganador(bool& fue_empate);

    void pudo_cambiar_de_arma(bool& pudo_cambiar);

    private:

    bool crear_provisiones_en_turno();

    
};

#endif
