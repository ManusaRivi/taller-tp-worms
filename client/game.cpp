#include "game.h"

using namespace SDL2pp;

#define GAME_MOVE_RIGHT 0x01
#define GAME_MOVE_LEFT 0x02

Game::Game(Queue<Snapshot> &queue, Queue<Comando> &acciones_):snapshots(queue), acciones(acciones_){}

int Game::run() try {

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

    /*Esto luego estara en un gestor de texturas*/
/*******************************************************************************/
    // Agrego el sprite del gusano caminando como una textura
    // Ademas, pongo como color transparente el color de fondo de la imagen
    // (Que tiene codigo RGB (128, 128, 192, 255))
	SDL_Color colorKey = {128, 128, 192, 255};
	Surface surface(DATA_PATH "/wwalk.png");
	Uint32 key = SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b);
	surface.SetColorKey(true, key);
    Texture wwalk(renderer, surface);
/*******************************************************************************/
    int run_phase = -1;      // Fase de la animacion para los worms (ver como arreglar)

    //unsigned int prev_ticks = SDL_GetTicks();

    // Loop principal
	while (1) {
		// Timing: calcula la diferencia entre este frame y el anterior
		// en milisegundos
		unsigned int frame_ticks = SDL_GetTicks();
		//unsigned int frame_delta = frame_ticks - prev_ticks;
		//prev_ticks = frame_ticks;

        // Procesamiento de eventos:
		// - Si la ventana se cierra o se presiona Esc
		//   cerrar la aplicacion.
		// - Si se presiona (KEYDOWN) la fecha derecha el gusano se mueve.
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			
			Comando cmd;
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					return 0;
				case SDLK_RIGHT: 
					cmd.agregar_tipo(0x01);
					cmd.agregar_direccion(GAME_MOVE_RIGHT);
					//ptcl.enviar_movimiento(GAME_MOVE_RIGHT); 
					break;
				case SDLK_LEFT: 
					cmd.agregar_tipo(0x01);
					cmd.agregar_direccion(GAME_MOVE_LEFT);
					//ptcl.enviar_movimiento(GAME_MOVE_LEFT); 
					break;
				}
            }
			acciones.push(cmd);
        }
		std::cout << "Se sale del while loop" << std::endl;
        //Ajusto la fase de la animacion de correr a la velocidad del procesador
        run_phase = (frame_ticks / 100) % 15;

        // La coordenada en Y del centro de la ventana
        int vcenter = renderer.GetOutputHeight() / 2;

        // Limpio la pantalla
		renderer.Clear();

        //Saco una Snapshot de la Queue
        Snapshot snap = snapshots.pop();

        //Grafico la snapshot
        snap.present(run_phase, renderer, wwalk, vcenter);

        // Limitador de frames: Duermo el programa durante un tiempo para no consumir
        // El 100% del CPU.
		SDL_Delay(1);
    }


} catch (std::exception& e) {
	// En caso de error, lo imprimo y devuelvo 1.
	std::cerr << e.what() << std::endl;
	return 1;
}