#include "worm_state.h"

using namespace SDL2pp;

WormState::WormState() {}

void WormState::present(int& it,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    std::vector<float>& position) {
    
    //Seteo como graficar los sprites:
    //Los sprites son de 60x60
	int src_x = 0;
	int src_y = 60 * (it % frames);

    //Voltear el sprite dependiendo para que lado mire
    int flip = facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    //Obtengo la textura
	Texture& texture = texture_manager.get_texture(texture_name);
	
	//Grafico al gusano:
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>(position[0] * 100), 480 - static_cast<int>(position[1] * 100) - 60, 60, 60), // Donde lo grafico
				worm_angle,        // Angulo
				NullOpt,
				flip        // Flip
			);
}