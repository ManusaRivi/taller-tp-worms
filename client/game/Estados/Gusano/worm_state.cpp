#include "worm_state.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
using namespace SDL2pp;

WormState::WormState(): iteration(0) {}

void WormState::present(int& it_inc,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
					float& pos_x,
					float& pos_y,
					float& x_scale,
					float& y_scale,
					int& vida) {
    
	SDL_Rect barraDeVida;
	barraDeVida.w = static_cast<int>(WORM_WIDTH * x_scale * (static_cast<float>(vida) / 100));
	barraDeVida.h = 5;

	barraDeVida.x = static_cast<int>(pos_x * x_scale);

	barraDeVida.y = renderer.GetOutputHeight() - static_cast<int>(pos_y * y_scale) - 10;

	SDL_Color colorBarraVida;
	if (vida <= 10) { // Vida es muy baja
	    colorBarraVida = {255, 0, 0, 255}; // Rojo
	} else {
	    colorBarraVida = {0, 255, 0, 255}; // Verde
	}

	SDL_SetRenderDrawColor(renderer.Get(), colorBarraVida.r, colorBarraVida.g, colorBarraVida.b, colorBarraVida.a);
	SDL_RenderFillRect(renderer.Get(), &barraDeVida);



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
    // printf("la posicion del gusano es %f %f\n",pos_x,pos_y);
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

float WormState::get_direction(){
	if (facing_right){
		return 0;
	}
	else{
		return 1;
	}
}

float WormState::get_shooting_angle(){
	return this->shot_angle;
}

float WormState::get_worm_angle(){
	return this->worm_angle;
}