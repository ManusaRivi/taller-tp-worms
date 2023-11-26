#include "explosion.h"

using namespace SDL2pp;

ExplosionCliente::ExplosionCliente(uint32_t id_, float x_, float y_, float radio_explosion_):
                                    id(id_), x(x_), y(y_),radio_explosion(radio_explosion_) {}

void ExplosionCliente::present(SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y){

}

int ExplosionCliente::get_id() {
    return id;
}

float ExplosionCliente::get_x() {
    return x;
}

float ExplosionCliente::get_y() {
    return y;
}
