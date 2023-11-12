#include "game.h"

using namespace SDL2pp;

#define GAME_MOVE_RIGHT 0x01
#define GAME_MOVE_LEFT 0x02

Game::Game(Queue<Mensaje> &queue, Queue<Mensaje> &acciones_):snapshots(queue), acciones(acciones_){}

int Game::run() try {

	printf("Se esta esperando por el handshake\n");
	std::vector<uint32_t> id_gusanos;
	uint32_t id_player;
	bool se_recibieron_ids = false;
	while(!se_recibieron_ids){
		Mensaje msg = snapshots.pop();
		if (msg.tipo_comando == COMANDO::CMD_HANDSHAKE){
			printf("Se popea un handshake\n");
			id_gusanos = msg.id_gusanos;
			id_player = msg.id_player;
			acciones.push(msg);
			se_recibieron_ids = true;
		}
	}

	printf("El id del player es : %u", id_player);
	


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

    TextureManager texture_manager(renderer);

	// Tomo el tiempo actual
    unsigned int t1 = SDL_GetTicks();

	// Numero de frame de la iteracion de las animaciones
	int it = 0;

	//Variables de teclas:
	bool right_press = false;
	bool left_press = false;
    // Loop principal
	while (1) {
        // Procesamiento de eventos:
		// - Si la ventana se cierra o se presiona Esc
		//   cerrar la aplicacion.
		// - Si se presiona (KEYDOWN) la fecha derecha el gusano se mueve.
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				SDL_Keycode tecla = event.key.keysym.sym;
				if (tecla == SDLK_ESCAPE){
					return 0;
				} else if (tecla == SDLK_RIGHT && !right_press) {
					right_press = true;
					std::shared_ptr<Comando> cmd;
					cmd = factory.accion_mover(GAME_MOVE_RIGHT);
					Mensaje msg(cmd);
					acciones.push(msg);
				} else if (tecla == SDLK_LEFT && !left_press) {
					left_press = true;
					std::shared_ptr<Comando> cmd;
					cmd = factory.accion_mover(GAME_MOVE_LEFT);
					Mensaje msg(cmd);
					acciones.push(msg);
				}
			} else if (event.type == SDL_KEYUP) {
				SDL_Keycode tecla = event.key.keysym.sym;
				if (tecla == SDLK_RIGHT) {
					right_press = false;
					std::shared_ptr<Comando> cmd;
					cmd = factory.accion_detener();
					Mensaje msg(cmd);
					acciones.push(msg);
				} else if (tecla == SDLK_LEFT) {
					left_press = false;
					std::shared_ptr<Comando> cmd;
					cmd = factory.accion_detener();
					Mensaje msg(cmd);
					acciones.push(msg);
				}
			}
        }
        // La coordenada en Y del centro de la ventana
        int vcenter = renderer.GetOutputHeight() / 2;

        // Limpio la pantalla
		renderer.Clear();

        //Saco una Snapshot de la Queue
        Mensaje snap = snapshots.pop();
		if (snap.tipo_comando == COMANDO::CMD_ENVIAR_SNAPSHOT){
			Snapshot snapshot = snap.snap;
			//Grafico la snapshot
			snapshot.present(it, renderer, texture_manager, vcenter);
		}
        printf("Se salta el snapshot\n");
		// Timing: calcula la diferencia entre este frame y el anterior
		// en milisegundos
		// If behind, drop & rest.
		unsigned int t2 = SDL_GetTicks();
		int rest = FRAME_RATE - (t2 - t1);
		
		if (rest < 0) {
			int behind = -rest;
			rest = FRAME_RATE - behind % FRAME_RATE;
			int lost = behind + rest;
			t1 += lost;
			it += int(lost / FRAME_RATE);
		}

        // Limitador de frames: Duermo el programa durante un tiempo para no consumir
        // El 100% del CPU.
		SDL_Delay(rest);
		t1 += FRAME_RATE;
		it += 1;
    }


} catch (std::exception& e) {
	// En caso de error, lo imprimo y devuelvo 1.
	std::cerr << e.what() << std::endl;
	return 1;
}