#ifndef BEAM_H
#define BEAM_H

#include <SDL2pp/SDL2pp.hh>
#include "../Texturas/texture_manager.h"

using namespace SDL2pp;

class Beam {
    private:
    int _tamaño;
    float _pos_x;
    float _pos_y;

    public:
    Beam(int& tamaño, float& pos_x, float& pos_y);

    void present(Renderer& renderer,
                    TextureManager& texture_manager,
                    float& x_scale,
                    float& y_scale,
                    float& camera_x,
                    float& camera_y);

};

#endif