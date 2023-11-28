#ifndef EXPLOSION_CLIENTE_H
#define EXPLOSION_CLIENTE_H
#include <SDL2pp/SDL2pp.hh>
#include <string>
#include "../Texturas/texture_manager.h"
#include <cstdint>

#define EXPLOSION_SPRITE_FRAMES 8

class ExplosionCliente {
    private:
    uint32_t id;
    int iteration;
    bool finished;
    float x;
    float y;
    float radio_explosion;

    public:
    ExplosionCliente(uint32_t id_,
                    float x_,
                    float y_,
                    float radio_explosion_);

    virtual void present(int& it_inc,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y);

    bool is_finished();

    float get_x();
    float get_y();
    int get_id();

};

#endif
