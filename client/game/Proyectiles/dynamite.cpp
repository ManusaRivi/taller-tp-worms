#include "dynamite.h"

using namespace SDL2pp;

Dynamite::Dynamite(float& pos_x, float& pos_y, float& angle):
                    ProjectileClient("Dynamite", pos_x, pos_y, angle) {}

void Dynamite::present(SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y) {
    
    // Calculo posicion relativa:
    float pos_rel_x = _pos_x - camera_x;
    float pos_rel_y = map_height - _pos_y - camera_y;

    // Frame (falta agregar it_inc para reproducir animacion)
    int src_x = 0;
    int src_y = 0;

    // Obtengo la textura
	Texture& texture = texture_manager.get_texture(texture_name);

    // Grafico
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    
    renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>((pos_rel_x - PROJECTILE_WIDTH/2) * x_scale),
					static_cast<int>((pos_rel_y - PROJECTILE_HEIGHT /2) * y_scale),
					PROJECTILE_WIDTH * x_scale, PROJECTILE_HEIGHT * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}