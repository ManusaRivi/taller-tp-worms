#include "w_jump.h"

using namespace SDL2pp;

WJump::WJump(bool& facing_right,
            float& worm_angle) {
    this->texture_name = "WJump";
    this->frames = 6;
    this->facing_right = facing_right;
    this->worm_angle = worm_angle;
    this->shot_angle = 0.0;
    this->finished = false;
}

bool WJump::change_position() {
    return true;
}

void WJump::present(int& it_inc,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
					float& pos_x,
					float& pos_y,
					float& x_scale,
					float& y_scale,
					int& vida) {
    
    //Seteo como graficar los sprites:
    //Los sprites son de 60x60

	iteration += it_inc;

    if (iteration >= frames) {
        iteration = frames;
        finished = true;
    }
	int src_x = 0;
	int src_y = 60 * iteration;

    //Voltear el sprite dependiendo para que lado mire
    int flip = facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    //Obtengo la textura
	Texture& texture = texture_manager.get_texture(texture_name);

	//Grafico
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    // printf("la posicion del gusano es %f %f\n",pos_x,pos_y);

	renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>((pos_x - WORM_WIDTH /2 - (0.85*WORM_WIDTH)) * x_scale),
					static_cast<int>((pos_y - WORM_HEIGHT /2 + (0.28*WORM_HEIGHT)) * y_scale),
					WORM_WIDTH * x_scale, WORM_HEIGHT * y_scale), // Donde lo grafico
				worm_angle,        // Angulo
				NullOpt,
				flip        // Flip
			);


	SDL_Rect barraDeVida;
	barraDeVida.w = static_cast<int>(WORM_WIDTH * x_scale * (static_cast<float>(vida) / 100));
	barraDeVida.h = 5;

	barraDeVida.x = static_cast<int>((pos_x - WORM_WIDTH /2 - (0.85*WORM_WIDTH)) * x_scale);

	barraDeVida.y = static_cast<int>((pos_y - 1 + (WORM_WIDTH/2)) * y_scale);

	SDL_Color colorBarraVida;
	if (vida <= 10) { // Vida es muy baja
	    colorBarraVida = {255, 0, 0, 255}; // Rojo
	} else {
	    colorBarraVida = {0, 255, 0, 255}; // Verde
	}

	SDL_SetRenderDrawColor(renderer.Get(), colorBarraVida.r, colorBarraVida.g, colorBarraVida.b, colorBarraVida.a);
	SDL_RenderFillRect(renderer.Get(), &barraDeVida);
}