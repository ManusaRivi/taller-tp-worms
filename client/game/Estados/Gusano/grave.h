#ifndef GRAVE_H
#define GRAVE_H

#include "worm_state.h"

class Grave: public WormState {
    public:
    //Constructor
    Grave(bool& facing_right, float& worm_angle);
    void present(int& it,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& pos_x,
                    float& pos_y,
                    float& x_scale,
                    float& y_scale,
                    int& vida,
                    uint32_t& equipo) override;
};

#endif