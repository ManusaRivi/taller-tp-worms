#ifndef WORM_STATE_H
#define WORM_STATE_H

#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <vector>
#include "../../Texturas/texture_manager.h"

#define WORM_WIDTH 0.4f
#define WORM_HEIGHT 0.4f

/*
 * Modela el estado del gusano para poder renderizarlo.
 */
class WormState {
    protected:
    std::string texture_name;
    unsigned int frames;
    bool facing_right;
    float worm_angle;
    float shot_angle;
    bool finished;

    //Constructor protegido para que solo las hijas puedan acceder a el
    WormState();

    public:
    //Renderiza el gusano en este estado
    virtual void present(int& it,
                        SDL2pp::Renderer& renderer,
                        TextureManager& texture_manager,
                        float& pos_x,
                        float& pos_y,
                        float& x_scale,
                        float& y_scale);
    
    virtual bool is_finished();

    //Destructor virtual
    virtual ~WormState() {}
};

#endif