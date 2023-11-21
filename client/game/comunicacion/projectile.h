#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include "../Texturas/texture_manager.h"

#define CANT_FRAMES 32
#define START_ANGLE 270
#define INC_ANGLE 11.25f

#define PROJECTILE_WIDTH 1.2
#define PROJECTILE_HEIGHT 1.2

/*
 * Representa el proyectil
 * ToDo:    Cambiar a clase abstracta con descendientes
 *          cuando haya mas que un unico tipo de proyectil.
 */
class Projectile {
    protected:
    std::string texture_name;
    int frames;
    float _pos_x;
    float _pos_y;
    float _angle;

    public:
    Projectile();

    virtual void present(SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y);
    
    //Destructor virtual
    virtual ~Projectile() {}
};

#endif