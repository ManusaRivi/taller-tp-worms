#ifndef WORM_H
#define WORM_H

#include <vector>
#include <string>
#include <SDL2pp/SDL2pp.hh>
#include "../Texturas/texture_manager.h"
#include "../Estados/Gusano/worm_state.h"

using namespace SDL2pp;

class Worm {
    private:
    float _pos_x;
    float _pos_y;
    std::unique_ptr<WormState> state;        
    
    public:
    //Constructor
    Worm(float& pos_x, float& pos_y, std::unique_ptr<WormState> state);

    //Constructor por copia:
    Worm(const Worm& other);

    Worm& operator=(const Worm& other);

    void update(std::shared_ptr<Worm> updated_worm);

    std::unique_ptr<WormState> get_state();

    void present(int& it_inc,
                Renderer& renderer,
                TextureManager& texture_manager,
                float& x_scale,
                float& y_scale,
                float& camera_x,
                float& camera_y);

    float get_x();

    float get_y();
};

#endif