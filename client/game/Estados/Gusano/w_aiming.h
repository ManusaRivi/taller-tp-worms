#ifndef W_AIMING_H
#define W_AIMING_H

#include "worm_state.h"

class WAiming: public WormState {
    public:
    WAiming(const std::string& texture_name,
            unsigned int& frames,
            bool& facing_right,
            float& worm_angle,
            float& shot_angle);


    virtual void present(int& it,
                        SDL2pp::Renderer& renderer,
                        TextureManager& texture_manager,
                        std::vector<float>& position,
                        float& x_scale,
                        float& y_scale) override;
};

#endif