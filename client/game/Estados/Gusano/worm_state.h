#ifndef WORM_STATE_H
#define WORM_STATE_H

#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <vector>
#include "../../Texturas/texture_manager.h"

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

    //Constructor protegido para que solo las hijas puedan acceder a el
    WormState();

    public:
    //Renderiza el gusano en este estado
    virtual void present(int& it,
                        SDL2pp::Renderer& renderer,
                        TextureManager& texture_manager,
                        std::vector<float>& position);

    //Destructor virtual
    virtual ~WormState() {}
};

#endif