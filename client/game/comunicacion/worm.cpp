#include "worm.h"

Worm::Worm(std::vector<float> position, int dir, int status): 
            position(position), dir(dir), status(status) {}

std::string Worm::determine_texture(int status) {
	switch (status) {
	case 0:
		return "wwalk";
	
	case 1:
		return "wwalk";

	default:
		return "wwalk";
	}
}

void Worm::present(int& run_phase, Renderer& renderer, TextureManager& texture_manager, int& vcenter) {
    //Seteo como graficar los sprites:
    //Si esta caminando, que frame ejecuto
    //Los sprites son de 60x60
		int src_x = 0, src_y = 0; // Por defecto el sprite quieto
		if (status == STATUS_MOVING) {
			src_x = 0;
			src_y = 60 * run_phase;
		}

    //Voltear el sprite dependiendo para que lado mire
    int flip = (dir == DIR_RIGHT) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    //Obtengo la textura
	std::string texture_name = determine_texture(status);
	Texture& texture = texture_manager.get_texture(texture_name);
	
	//Grafico al gusano:
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>(position[0] * 100), 480 - static_cast<int>(position[1] * 100) - 60, 60, 60), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				flip        // Flip
			);

}