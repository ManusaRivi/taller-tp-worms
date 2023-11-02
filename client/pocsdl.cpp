#include "pocsdl.h"

using namespace SDL2pp;
#define GAME_MOVE_RIGHT 0x01
#define GAME_MOVE_LEFT 0x02

SDLPoc::SDLPoc(Queue<Snapshot> &queue, Queue<std::shared_ptr<Comando>> &acciones_) : snapshots(queue), acciones(acciones_) {}

int SDLPoc::run() try {
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
    // (Que tiene codigo RGB (128, 128, 192, 255))
	SDL_Color colorKey = {128, 128, 192, 255};
	Surface surface(DATA_PATH "/wwalk.png");
	Uint32 key = SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b);
	surface.SetColorKey(true, key);
    Texture sprites(renderer, surface);

    // Cargo la fuente del texto de arriba a la derecha (Vera, con tamaño de 12pt)
	Font font(DATA_PATH "/Vera.ttf", 12);

    // Estado del juego
	bool is_running = false; // Si el gusano esta caminando
	bool mira_derecha = true;
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
			
			std::shared_ptr<Comando> cmd;
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					return 0;
				case SDLK_RIGHT: 
					cmd = factory.accion_mover(GAME_MOVE_RIGHT);
					//ptcl.enviar_movimiento(GAME_MOVE_RIGHT); 
					break;
				case SDLK_LEFT: 
					cmd = factory.accion_mover(GAME_MOVE_LEFT);
					//ptcl.enviar_movimiento(GAME_MOVE_LEFT); 
					break;
				}
            }
			acciones.push(std::move(cmd));
        }

        // Actualizar el estado del juego en este frame:
		// Si el gusano esta corriendo, moverlo a la derecha
        //La animacion tiene 15 frames
		float velocidad = mira_derecha ? 0.1 : -0.1;
		if (is_running) {
			position += frame_delta * velocidad;
			run_phase = (frame_ticks / 100) % 15;
		} else {
			run_phase = 0;
		}

        // Si el gusano se sale de la pantalla, lo teletransporto
		// al lado izquierdo
		if (position > renderer.GetOutputWidth() || position < 0)
			position = 0;

        // La coordenada en Y del centro de la ventana
        int vcenter = renderer.GetOutputHeight() / 2;

		// Limpio la pantalla
		renderer.Clear();

        // Elijo el sprite segun si el jugador esta caminando o no
        // Y ejecuto la fase de animacion.

        //Los sprites son de 60x60
		int src_x = 0, src_y = 0; // Por defecto el sprite quieto
		if (is_running) {
			src_x = 0;
			src_y = 60 * run_phase;
		}

        // Dibujo el sprite del gusano
		// Y lo volteo, dependiendo a donde mire
		int flip = mira_derecha ?  SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		sprites.SetAlphaMod(255); // El sprite es totalmente opaco
		renderer.Copy(
				sprites,
				Rect(src_x, src_y, 60, 60),
				Rect((int)position, vcenter - 60, 60, 60),
				0.0,
				NullOpt,
				flip
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
