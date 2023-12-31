#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include <memory>
#include <string>
#include "comunicacion/worm.h"
#include "comunicacion/beam.h"
#include "comunicacion/provision.h"
#include "camara.h"
#include "comunicacion/projectile.h"
#include "comunicacion/explosion.h"
#include "comunicacion/provision.h"
#include "Sonidos/sound_manager.h"
#include "../../common/armas.h"
#include "../../common/fondos.h"

#define WATER_SPRITE_WIDTH 1920
#define WATER_SPRITE_HEIGHT 64

#define WATER_HEIGHT 8

#define HUD_SPRITE_WIDTH 320
#define HUD_SPRITE_HEIGHT 64

#define POWER_HEIGHT 1
#define MAX_POWER 40

#define SIGHT_DIAMETER 1
#define SIGHT_SPRITE_DIAMETER 32

#define WIND_HEIGHT 1
#define WIND_SPRITE_WIDTH 96
#define WIND_SPRITE_HEIGHT 13

#define ARROW_SPRITE_SIDE 60
#define ARROW_SIDE 3
#define ARROW_FRAMES 30

#define TEAM_HEALTH_HEIGHT 1

class World {
    private:
    std::map<int, std::shared_ptr<Worm>> worms;
    std::vector<Beam> beams;
    std::map<int, std::unique_ptr<ProjectileClient>> projectiles;
    std::map<int, ExplosionCliente> explosions; 
    std::map<int, ProvisionClient> provisiones;
    std::vector<int> sonidos;
    int _id_camera;
    uint32_t _id_actual_turn;
    float camera_x;
    float camera_y;
    int proy_it;
    float _map_width;
    float _map_height;

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

    bool _wind_left;
    float _wind;

    int it_arrow;

    std::string back_name;
    int back_width;
    int back_height;

    void present_background(Renderer& Renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale,
                        float& camera_x,
                        float& camera_y);

    void present_water(Renderer& Renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale,
                        float& camera_x,
                        float& camera_y);   

    void present_hud(Renderer& renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale);
    
    void present_weapon_power(Renderer& renderer,
                            TextureManager& texture_manager,
                            float& x_scale,
                            float& y_scale);

    void present_timer(Renderer& renderer,
                            TextureManager& texture_manager,
                            float& x_scale,
                            float& y_scale);

    void present_sight(Renderer& renderer,
                            TextureManager& texture_manager,
                            float& pos_x,
                            float& pos_y,
                            float& x_scale,
                            float& y_scale,
                            float& camera_x,
                            float& camera_y);

    void present_ammo(Renderer& renderer,
                            TextureManager& texture_manager,
                            float& x_scale,
                            float& y_scale);

    void present_wind(Renderer& renderer,
                            TextureManager& texture_manager,
                            float& x_scale,
                            float& y_scale);
    
    void present_turn_arrow(int& it_inc,
                            Renderer& renderer,
                            TextureManager& texture_manager,
                            float& x_scale,
                            float& y_scale,
                            float& camera_x,
                            float& camera_y);

    SDL_Color hashEquipo(uint32_t& indice);

    void present_teams_health(Renderer& renderer,
                            TextureManager& texture_manager,
                            float& x_scale,
                            float& y_scale);

    public:
    World(float map_width, float map_height, int background_type);

    std::vector<Beam> get_beams();
    std::map<int, std::shared_ptr<Worm>> get_worms();

    void update_camera(int id_camera);

    void update_turn(uint32_t id_actual_turn);

    uint32_t get_turn();

    void add_worm(std::shared_ptr<Worm> worm, int id);

    void add_sound(int sound_code);

    void update_worm(const int& id, std::shared_ptr<Worm> worm);

    void add_beam(Beam beam);

    void add_projectile(std::unique_ptr<ProjectileClient> projectile);

    void add_provision(ProvisionClient provision);

    std::vector<int> get_projectile_ids();

    void add_explosion(ExplosionCliente explosion);

    void update_wind(bool& wind_left, float& wind);

    bool checkOnePlayerRemains();

    void present(int& it_inc,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        SoundManager& sound_manager,
                        Mixer& mixer,
                        float& x_scale,
                        float& y_scale,
                        Camara& camara);

    float get_camera_x();
    float get_camera_y();
    float get_map_height();

    void set_weapon_power(int& power);

    void set_tp(bool& _has_tp, float& pos_x, float& pos_y);

    void set_air_attack(bool& _has_air_attack, float& pos_x, float& pos_y);

    void set_timer(bool& _has_timer, int& _timer);

    void set_ammo(const int& weapon, const int& _ammo);

};

#endif