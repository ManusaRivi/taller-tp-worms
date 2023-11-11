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
    std::vector<float> position;  // (x,y)
    std::unique_ptr<WormState> state;              
    
    public:
    //Constructor
    Worm(std::vector<float> position, std::unique_ptr<WormState> state);

    //Constructor por copia:
    Worm(const Worm& other);

    Worm& operator=(const Worm& other);


    //La idea es que despues deje de recibir una unica textura
    //Y reciba un gestor de textura para pedirle la textura a mostrar
    void present(int& it,
                Renderer& renderer,
                TextureManager& texture_manager,
                int& vcenter);
};

#endif