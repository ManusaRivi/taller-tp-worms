#include "worm_state.h"

using namespace SDL2pp;

WormState::WormState(): iteration(0) {}

void WormState::present(int& it_inc,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
					float& pos_x,
					float& pos_y,
					float& x_scale,
					float& y_scale) {
    
    //Seteo como graficar los sprites:
    //Los sprites son de 60x60

	iteration += it_inc;
	//iteration = it_inc;

	int src_x = 0;
	int src_y = 60 * (iteration % frames);

    //Voltear el sprite dependiendo para que lado mire
    int flip = facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    //Obtengo la textura
	Texture& texture = texture_manager.get_texture(texture_name);

	//Grafico
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>(pos_x * x_scale),
					renderer.GetOutputHeight() - static_cast<int>(pos_y * y_scale),
					WORM_WIDTH * x_scale, WORM_HEIGHT * y_scale), // Donde lo grafico
				worm_angle,        // Angulo
				NullOpt,
				flip        // Flip
			);
}

int WormState::get_iteration() {
	return iteration;
}

void WormState::set_iteration(int& it) {
	iteration = it;
}


bool WormState::is_finished() {
	return finished;
}