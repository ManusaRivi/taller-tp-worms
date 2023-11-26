#include "fragment.h"

using namespace SDL2pp;

Fragment::Fragment(float& pos_x, float& pos_y, float& angle):
                    ProjectileClient("Drop", pos_x, pos_y, angle) {}

void Fragment::present(SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y) {
    
    // Calculo posicion relativa:
    float pos_rel_x = _pos_x - camera_x;
    float pos_rel_y = map_height - _pos_y - camera_y;

    // Frame (tiene uno solo)
    int src_x = 0;
    int src_y = 0;

    // Obtengo la textura
	Texture& texture = texture_manager.get_texture(texture_name);

    // Grafico
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    
    renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>((pos_rel_x - FRAGMENT_WIDTH/2) * x_scale),
					static_cast<int>((pos_rel_y - FRAGMENT_HEIGHT /2) * y_scale),
					FRAGMENT_WIDTH * x_scale, FRAGMENT_HEIGHT * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);

}