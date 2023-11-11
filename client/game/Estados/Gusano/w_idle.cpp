#include "w_idle.h"

using namespace SDL2pp;

WIdle::WIdle(bool facing_right): 
            texture_name("wwalk"), facing_right(facing_right) {}

void WIdle::present(int& it, SDL2pp::Renderer& renderer,
                TextureManager& texture_manager, std::vector<int>& position) {
    
    int src_x = 0, src_y = 0;
    int flip = facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Texture& texture = texture_manager.get_texture(texture_name);
    texture.SetAlphaMod(255);
    renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>(position[0] * 100), 480 - static_cast<int>(position[1] * 100) - 60, 60, 60), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				flip        // Flip
			);
}