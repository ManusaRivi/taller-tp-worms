#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include <memory>
#include <string>
#include "comunicacion/worm.h"
#include "comunicacion/beam.h"
#include "camara.h"
#include "comunicacion/projectile.h"
#include "comunicacion/explosion.h"
#include "Sonidos/sound_manager.h"

#define BACKGROUND_WIDTH 576
#define BACKGROUND_HEIGHT 324

#define WATER_SPRITE_WIDTH 1920
#define WATER_SPRITE_HEIGHT 64

#define WATER_HEIGHT 8

#define HUD_SPRITE_WIDTH 320
#define HUD_SPRITE_HEIGHT 64

#define HUD_WIDTH 1
#define HUD_HEIGHT 0.2

class World {
    private:
    std::map<int, std::shared_ptr<Worm>> worms;
    std::vector<Beam> beams;
    std::map<int, std::unique_ptr<ProjectileClient>> projectiles;
    std::map<int, ExplosionCliente> explosions; 
    std::vector<int> sonidos;
    int _id_camera;
    int proy_it;
    float _map_width;
    float _map_height;

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

    void present_hud(Renderer& Renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale);

    public:
    World(float map_width, float map_height);

    std::vector<Beam> get_beams();
    std::map<int, std::shared_ptr<Worm>> get_worms();

    void update_camera(int id_camera);

    void add_worm(std::shared_ptr<Worm> worm, int id);

    void add_sound(int sound_code);

    void update_worm(const int& id, std::shared_ptr<Worm> worm);

    void add_beam(Beam beam);

    void add_projectile(std::unique_ptr<ProjectileClient> projectile);

    std::vector<int> get_projectile_ids();

    void add_explosion(ExplosionCliente explosion);

    void present(int& it_inc,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        SoundManager& sound_manager,
                        Mixer& mixer,
                        float& x_scale,
                        float& y_scale,
                        Camara& camara);

    // Metodos unicamente para testear

};

#endif