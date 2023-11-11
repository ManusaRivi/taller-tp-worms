#ifndef W_IDLE_H
#define W_IDLE_H

#define FRAMES 1

#include "worm_state.h"
// Gusano Quieto
class WIdle: public WormState {
    public:
    std::string texture_name;
    bool facing_right;
    //Constructor
    WIdle(bool facing_right);

    void present(int& it, SDL2pp::Renderer& renderer,
                TextureManager& texture_manager,
                std::vector<int>& position) override;
};

#endif