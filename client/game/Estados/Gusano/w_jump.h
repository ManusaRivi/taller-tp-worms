#ifndef W_JUMP_H
#define W_JUMP_H

#include "worm_state.h"

class WJump: public WormState {
    public:
    WJump(bool& facing_right,
            float& worm_angle);

    virtual bool change_position() override;

    virtual void present(int& it_inc,
                        SDL2pp::Renderer& renderer,
                        TextureManager& texture_manager,
                        float& pos_x,
                        float& pos_y,
                        float& x_scale,
                        float& y_scale,
                        int& vida) override;
};

#endif