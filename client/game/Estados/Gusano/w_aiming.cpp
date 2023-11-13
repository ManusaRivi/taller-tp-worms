#include "w_aiming.h"

using namespace SDL2pp;

WAiming::WAiming(const std::string& texture_name, unsigned int& frames,
                bool& facing_right, float& worm_angle, float& shot_angle) {
    this->texture_name = texture_name;
    this->frames = frames;
    this->facing_right = facing_right;
    this->worm_angle = worm_angle;
    this->shot_angle = shot_angle;
}

void WAiming::present(int& it,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    std::vector<float>& position,
                    float& x_scale,
                    float& y_scale) {
    
    //Determino cual frame usar:
    int shot_angle_from = shot_angle + 90;
    int src_x = 0;
	int src_y = 60 * (shot_angle_from % frames);


    //Voltear el sprite dependiendo para que lado mire
    int flip = facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    //Obtengo la textura
	Texture& texture = texture_manager.get_texture(texture_name);

    //Grafico al gusano:
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