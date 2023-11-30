#include "worm_state.h"
#include <yaml-cpp/yaml.h>

using namespace SDL2pp;

WormState::WormState(): iteration(0) {}

void WormState::present(int& it_inc,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
					float& pos_x,
					float& pos_y,
					float& x_scale,
					float& y_scale,
					int& vida,
					uint32_t& equipo) {
    
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
				Rect(static_cast<int>((pos_x - WORM_WIDTH / 2) * x_scale),
					static_cast<int>((pos_y - WORM_HEIGHT / 2) * y_scale),
					WORM_WIDTH * x_scale, WORM_HEIGHT * y_scale), // Donde lo grafico
				worm_angle,        // Angulo
				NullOpt,
				flip        // Flip
			);

	this->setBarraVida(renderer, pos_x, pos_y, x_scale, y_scale, vida, equipo);
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

bool WormState::change_position() {
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

SDL_Color WormState::hashEquipo(uint32_t& indice) {

    SDL_Color colores[NUM_COLORES] = {
        {0, 0, 255, 255},   // Azul
        {255, 255, 0, 255}, // Amarillo
        {0, 255, 255, 255},  // Cian
        {255, 0, 255, 255}, // Magenta
        {255, 165, 0, 255}  // Naranja
    };

    uint32_t indiceCircular = indice % NUM_COLORES;

    return colores[indiceCircular];
}

void WormState::setBarraVida(SDL2pp::Renderer& renderer, float& pos_x, float& pos_y, float& x_scale, float& y_scale, int& vida, uint32_t& equipo) {
	
	SDL_Rect barraDeVida;
	barraDeVida.w = static_cast<int>(WORM_WIDTH * x_scale * (static_cast<float>(vida) / 100));
	barraDeVida.h = 5;

	barraDeVida.x = static_cast<int>((pos_x - WORM_WIDTH/2) * x_scale);

	barraDeVida.y = static_cast<int>((pos_y - 1 - (WORM_HEIGHT/2)) * y_scale);

	SDL_Color colorBarraVida;
	SDL_Color colorBorde;

	if (vida <= 10) { // Vida es muy baja
	    colorBarraVida = {255, 0, 0, 255}; // Rojo
	} else {
	    colorBarraVida = {0, 255, 0, 255}; // Verde
	}

	colorBorde = hashEquipo(equipo);

	SDL_SetRenderDrawColor(renderer.Get(), colorBarraVida.r, colorBarraVida.g, colorBarraVida.b, colorBarraVida.a);
	SDL_RenderFillRect(renderer.Get(), &barraDeVida);

	// Dibuja el borde
	SDL_SetRenderDrawColor(renderer.Get(), colorBorde.r, colorBorde.g, colorBorde.b, colorBorde.a);
	SDL_RenderDrawRect(renderer.Get(), &barraDeVida);
}
