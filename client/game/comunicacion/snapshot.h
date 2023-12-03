#ifndef SNAPSHOT_CLIENTE
#define SNAPSHOT_CLIENTE

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <vector>
#include "../Texturas/texture_manager.h"
#include "../world.h"
#include "worm.h"
#include "beam.h"
#include "explosion.h"
#include "provision.h"
#include "../Proyectiles/projectile_generator.h"

#include <memory>

using namespace SDL2pp;

// Simula la "imagen" del estado del juego.
class SnapshotCliente {
    private:
    std::map<int, std::shared_ptr<Worm>> worms;
    std::vector<Beam> beams;
    int _id_camera;
    uint32_t id_turno_actual;
    std::vector<std::unique_ptr<ProjectileClient>> projectiles;
    std::vector<int> sonidos;
    std::vector<ExplosionCliente> explosiones;
    std::vector<ProvisionClient> provisiones;
 

    int weapon_power;

    bool has_tp;
    float tp_x;
    float tp_y;

    bool has_air_attack;
    float air_attack_x;
    float air_attack_y;

    bool has_timer;
    int timer;

    std::map<int, int> ammo;

    public:
    //Constructor
    SnapshotCliente(int id_camera);

    std::map<int, std::shared_ptr<Worm>> get_worms();

    //Agrega un gusano a la lista de gusanos
    void add_worm(std::shared_ptr<Worm> worm, int id);

    void add_beam(Beam beam);

    void add_projectile(std::unique_ptr<ProjectileClient> projectil);

    void add_provision(ProvisionClient provision);

    void add_sound(int sound_code);

    void add_explosion(ExplosionCliente explosion);

    void set_weapon_power(int& power);

    void set_tp(bool& has_tp, float& pos_x, float& pos_y);

    void set_air_attack(bool& _has_air_attack, float& pos_x, float& pos_y);

    void set_timer(bool& _has_timer, int& _timer);

    void set_ammo(int& weapon, int& _ammo);

/*
    void present(int& it_inc,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        int& window_width,
                        int& window_height,
                        float& x_scale,
                        float& y_scale);
*/

    void apply_to_world(World& world);

    bool turn_change(World& world);

    void agregar_turno_actual(uint32_t id);

    void imprimir_posiciones();

    void actulizar_camara(uint32_t id);


    
};

#endif
