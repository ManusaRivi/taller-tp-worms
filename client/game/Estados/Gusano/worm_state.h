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
    public:
    //Renderiza el gusano en este estado
    virtual void present(int& it,
                        SDL2pp::Renderer& renderer,
                        TextureManager& texture_manager,
                        std::vector<int>& position) = 0;

    //Destructor virtual
    virtual ~WormState() {}
};

#endif