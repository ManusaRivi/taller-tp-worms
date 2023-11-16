#include "beam.h"

using namespace SDL2pp;

Beam::Beam(int& tamaño, float& pos_x, float& pos_y): _tamaño(tamaño), _pos_x(pos_x), _pos_y(pos_y) {}

void Beam::present(Renderer& renderer,
                    TextureManager& texture_manager,
                    float& x_scale,
                    float& y_scale,
                    float& camera_x,
                    float& camera_y) {

    // Obtengo la textura
	Texture& texture = texture_manager.get_texture("Beam");

    int largo_sprite = _tamaño == 6 ? 138 : 69;

    float pos_rel_x = _pos_x - camera_x;
    float pos_rel_y = _pos_y - camera_y;

    // Grafico la viga
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    renderer.Copy(
				texture,
				Rect(0, 0, largo_sprite, 20), // El sprite
				Rect(static_cast<int>(pos_rel_x * x_scale),
					renderer.GetOutputHeight() - static_cast<int>(pos_rel_y * y_scale),
					_tamaño * x_scale, 0.87 * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}