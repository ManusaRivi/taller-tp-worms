#include "explosion.h"

using namespace SDL2pp;

ExplosionCliente::ExplosionCliente(uint32_t id_, float x_, float y_, float radio_explosion_):
                                    id(id_), iteration(0), finished(false), x(x_), y(y_),radio_explosion(radio_explosion_) {}

void ExplosionCliente::present(int& it_inc, SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y){
    iteration += it_inc;

    if (iteration >= EXPLOSION_SPRITE_FRAMES) {
        iteration = EXPLOSION_SPRITE_FRAMES;
        finished = true;
    }
	int src_x = 0;
	int src_y = 100 * iteration;

    //Obtengo la textura
    std::string texture_name = "Explosion";
	Texture& texture = texture_manager.get_texture(texture_name);

	//Grafico
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    // printf("la posicion del gusano es %f %f\n",pos_x,pos_y);

	renderer.Copy(
				texture,
				Rect(src_x, src_y, 100, 100), // El sprite
				Rect(static_cast<int>((x - radio_explosion) * x_scale),
					static_cast<int>((x - radio_explosion) * y_scale),
					radio_explosion*2 * x_scale, radio_explosion*2 * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}

bool ExplosionCliente::is_finished() {
    return finished;
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
