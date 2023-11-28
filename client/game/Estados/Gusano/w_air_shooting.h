#ifndef W_AIR_SHOOTING_H
#define W_AIR_SHOOTING_H

#include "worm_state.h"

class WAirShooting: public WormState {
    public:

    WAirShooting(bool& facing_right,float& worm_angle);

    virtual void present(int& it_inc,
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