#ifndef WBACKFLIP_H
#define WBACKFLIP_H

#include "worm_state.h"

class WBackflip: public WormState {
    public:

    WBackflip(bool& facing_right,float& worm_angle);

    virtual bool change_position() override;

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