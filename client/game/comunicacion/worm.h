#ifndef WORM_H
#define WORM_H

#include <vector>
#include <string>
#include <SDL2pp/SDL2pp.hh>
#include "../Texturas/texture_manager.h"

using namespace SDL2pp;

//Direcciones (despues quizas cambie a un angulo)
#define DIR_RIGHT 1
#define DIR_LEFT 0

//Estados (Despues va a haber mas)
#define STATUS_IDLE 0
#define STATUS_MOVING 1

class Worm {
    private:
    std::vector<float> position;  // (x,y)
    int dir;                    // Despues quizas cambie a un angulo
    int status;                 
    
    std::string determine_texture(int status);

    public:
    //Constructor
    Worm(std::vector<float> position, int dir, int status);

    //La idea es que despues deje de recibir una unica textura
    //Y reciba un gestor de textura para pedirle la textura a mostrar
    void present(int& run_phase,
                Renderer& renderer,
                TextureManager& texture_manager,
                int& vcenter);
};

#endif