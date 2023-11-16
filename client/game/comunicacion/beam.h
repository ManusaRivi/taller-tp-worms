#ifndef BEAM_H
#define BEAM_H

#include <SDL2pp/SDL2pp.hh>
#include "../Texturas/texture_manager.h"
#include <string>

#define BEAM_WIDTH 0.8

using namespace SDL2pp;

class Beam {
    private:
    int _tamano;
    float _pos_x;
    float _pos_y;

    public:
    Beam(int& tamano, float& pos_x, float& pos_y);

    void present(Renderer& renderer,
                    TextureManager& texture_manager,
                    float& x_scale,
                    float& y_scale,
                    float& camera_x,
                    float& camera_y);

};

#endif