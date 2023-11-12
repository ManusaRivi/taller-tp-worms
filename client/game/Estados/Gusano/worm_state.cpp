#include "worm_state.h"

using namespace SDL2pp;

WormState::WormState() {}

void WormState::present(int& it,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    std::vector<float>& position,
					float& x_scale,
					float& y_scale) {
    
    //Seteo como graficar los sprites:
    //Los sprites son de 60x60
	int src_x = 0;
	int src_y = 60 * (it % frames);

    //Voltear el sprite dependiendo para que lado mire
    int flip = facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    //Obtengo la textura
	Texture& texture = texture_manager.get_texture(texture_name);
	
	//Grafico al gusano:
	std::cout << "dibujo al gusano de tamaño: "
				<< WORM_WIDTH * x_scale << "x"
				<< WORM_HEIGHT * y_scale << " En la posicion x="
				<< static_cast<int>(position[0] * x_scale)
				<< " y="
				<< renderer.GetOutputHeight() - static_cast<int>(position[1] * y_scale)
				<< "\n";

	std::cout << "Posicion del gusano (metros): x=" << position[0]
				<< " y=" << position[1] << "\n";

    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>(position[0] * x_scale),
					renderer.GetOutputHeight() - static_cast<int>(position[1] * y_scale),
					WORM_WIDTH * x_scale, WORM_HEIGHT * y_scale), // Donde lo grafico
				worm_angle,        // Angulo
				NullOpt,
				flip        // Flip
			);
}