#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "../comunicacion/projectile.h"

#define FRAGMENT_HEIGHT 0.4
#define FRAGMENT_WIDTH 0.4

class Fragment: public ProjectileClient {
    public:

    Fragment(float& pos_x, float& pos_y, float& angle, uint32_t id);

    void present(int& it, SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y) override;
};

#endif