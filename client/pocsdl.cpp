#include "pocsdl.h"

using namespace SDL2pp;

int poc::run() try {
	// Inicializo SDL
	SDL sdl(SDL_INIT_VIDEO);

	// Inicializo SDL_ttf
	SDLTTF ttf;

    // Creo la ventana: 
    // Dimensiones: 640x480, redimensionable
    // Titulo: Worms
	Window window("Worms",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480,
			SDL_WINDOW_RESIZABLE);

    // Creo un renderizador default
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Agrego el sprite del gusano caminando como una textura
    // Ademas, pongo como color transparente el color de fondo de la imagen
    // (Que tiene codigo RGB hexadecimal 0x8080c0)
    Texture sprites(renderer, Surface("client/sprites/Worms/wwalk.png")
			.SetColorKey(true, 0x8080c0));

    // Cargo la fuente del texto de arriba a la derecha (Vera, con tamaño de 12pt)
	Font font(DATA_PATH "/Vera.ttf", 12);

    // Estado del juego
	bool is_running = false; // Si el gusano esta caminando
	int run_phase = -1;      // Fase de la animacion
	float position = 0.0;    // Posicion del gusano

    unsigned int prev_ticks = SDL_GetTicks();

    // Loop principal
	while (1) {
		// Timing: calcula la diferencia entre este frame y el anterior
		// en milisegundos
		unsigned int frame_ticks = SDL_GetTicks();
		unsigned int frame_delta = frame_ticks - prev_ticks;
		prev_ticks = frame_ticks;


        // Procesamiento de eventos:
		// - Si la ventana se cierra o se presiona Esc
		//   cerrar la aplicacion.
		// - Si se presiona (KEYDOWN) la fecha derecha el gusano se mueve.
		// - Si se deja de presionar (KEYUP) la flecha derecha el gusano deja de moverse.
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					return 0;
				case SDLK_RIGHT: is_running = true; break;
				}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT: is_running = false; break;
				}
			}
		}

        // Actualizar el estado del juego en este frame:
		// Si el gusano esta corriendo, moverlo a la derecha
        //La animacion tiene 15 frames
		if (is_running) {
			position += frame_delta * 0.2;
			run_phase = (frame_ticks / 100) % 15;
		} else {
			run_phase = 0;
		}

        // Si el gusano se sale de la pantalla, lo teletransporto
		// al lado izquierdo
		if (position > renderer.GetOutputWidth())
			position = -50;

        // La coordenada en Y del centro de la ventana
        int vcenter = renderer.GetOutputHeight() / 2;

		// Limpio la pantalla
		renderer.Clear();

        // Elijo el sprite segun si el jugador esta caminando o no
        // Y ejecuto la fase de animacion.

        //Los sprites son de 60x60
		int src_x = 0, src_y = 0; // Por defecto el sprite quieto
		if (is_running) {
			// uno de 15 sprites de caminar
			src_x = 60;
			src_y = 15 + 60 * run_phase;
		}

        // Dibujo el sprite del gusano
		sprites.SetAlphaMod(255); // El sprite es totalmente opaco
		renderer.Copy(
				sprites,
				Rect(src_x, src_y, 60, 60),
				Rect((int)position, vcenter - 60, 60, 60)
			);

        // Creo la cadena de texto para renderizar
		std::string text =
			"Position: "
			+ std::to_string((int)position)
			+ ", running: "
			+ (is_running ? "true" : "false");

        // Renderizo el texto en una nueva textura.
		Texture text_sprite(
				renderer,
				font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255})
			);
        
        // Copio la textura a la parte superior izquierda de la ventana
		renderer.Copy(text_sprite, NullOpt, Rect(0, 0, text_sprite.GetWidth(), text_sprite.GetHeight()));
    
        // Muestro el frame renderizado
		renderer.Present();

        // Limitador de frames: Duermo el programa durante un tiempo para no consumir
        // El 100% del CPU.
		SDL_Delay(1);
    }

    return 0;
} catch (std::exception& e) {
	// En caso de error, lo imprimo y devuelvo 1.
	std::cerr << e.what() << std::endl;
	return 1;
}