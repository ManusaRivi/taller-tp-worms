#include "beam.h"

Beam::Beam(int& tamaño, float& pos_x, float& pos_y): _tamaño(tamaño), _pos_x(pos_x), _pos_y(pos_y) {}

void Beam::present(Renderer& renderer,
                    TextureManager& texture_manager,
                    float& x_scale,
                    float& y_scale,
                    float& camera_x,
                    float& camera_y) {

    /*
        Obtener textura y mostrar segun el tamaño
    */
}