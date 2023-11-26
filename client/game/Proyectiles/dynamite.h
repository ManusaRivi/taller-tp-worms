#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "../comunicacion/projectile.h"

class Dynamite: public ProjectileClient {
    public:
    Dynamite(float& pos_x, float& pos_y, float& angle);

    virtual void present(SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y) override;
};

#endif