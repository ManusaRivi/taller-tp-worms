#ifndef PROJECTILE_H_CLIENT
#define PROJECTILE_H_CLIENT

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include "../Texturas/texture_manager.h"

#define CANT_FRAMES 32
#define START_ANGLE 270
#define INC_ANGLE 11.25f

#define PROJECTILE_WIDTH 2.3
#define PROJECTILE_HEIGHT 2.3

/*
 * Representa el proyectil
 * ToDo:    Cambiar a clase abstracta con descendientes
 *          cuando haya mas que un unico tipo de proyectil.
 */
class ProjectileClient {
    protected:
    std::string texture_name;
    float _pos_x;
    float _pos_y;
    float _angle;
    uint32_t id;

    public:
    ProjectileClient(const std::string texture, float& pos_x, float& pos_y, float& angle, uint32_t id_);

    virtual void present(int& it,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y);
    
    int get_id();

    float get_x();
    float get_y();



    void update(ProjectileClient other);

    float& get_x_test();
    float& get_y_test();
    
    //Destructor virtual
    virtual ~ProjectileClient() {}
};

#endif