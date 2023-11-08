#include "worm.h"

Worm::Worm(std::vector<float> position, int dir, int status): 
            position(position), dir(dir), status(status) {}

void Worm::present(int& run_phase, Renderer& renderer, Texture& wwalk, int& vcenter) {
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

    //Grafico al gusano:
    
	std::cout << "Gusano: ME VOY A GRAFICAR\n";
	std::cout << "Mis posiciones (X, Y) son: X=" << position[0] << " Y=" << position[1] << "\n";
	std::cout << "Las transformo a X=" << static_cast<int>(position[0] * 100) << " Y=" << 480 - static_cast<int>(position[1] * 100) << "\n";

    wwalk.SetAlphaMod(255); // El sprite es totalmente opaco
    renderer.Copy(
				wwalk,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>(position[0] * 100), 480 - static_cast<int>(position[1] * 100) - 60, 60, 60), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				flip        // Flip
			);

}