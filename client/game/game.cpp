#include "game.h"

using namespace SDL2pp;

#define GAME_MOVE_RIGHT 0x01
#define GAME_MOVE_LEFT 0x02

Game::Game(Queue<std::shared_ptr<Mensaje>> &queue, Queue<std::shared_ptr<Mensaje>> &acciones_):snapshots(queue), acciones(acciones_){}

int Game::run() try {

	World world;

	std::vector<uint32_t> id_gusanos;
	uint32_t id_player;
	bool se_recibieron_ids = false;
	while(!se_recibieron_ids){
		std::shared_ptr<Mensaje> msg = snapshots.pop();
		if (msg->tipo_comando == COMANDO::CMD_HANDSHAKE){
			id_gusanos = msg->id_gusanos;
			id_player = msg->id_player;
			acciones.push(msg);
			se_recibieron_ids = true;

			/*
				En el Handshake deberia recibir las posiciones de las vigas 
				Y las posiciones iniciales de todos los gusanos (como una snapshot)

				* Idea: Crear world en el protocolo de esta manera:
			
					World world();
					Por cada Worm:
						world.add_worm(worm, id);

					Por cada viga:
						world.add_beam(beam);
			

					Y guardarlo en el msg de tipo handshake.
					Luego, reemplazar este comentario con:
				
					world = msg->world;
			*/
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
			854, 480,
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
	bool up_press = false;
	bool down_press = false;
	bool return_press = false;
	bool backspace_press = false;
	bool has_selected_weapon = false;
	bool is_aiming = false;
	bool is_charging_power = false;
    // Loop principal
	while (1) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				SDL_Keycode tecla = event.key.keysym.sym;
				if (tecla == SDLK_ESCAPE){
					return 0;
				} else if (tecla == SDLK_RIGHT && !right_press && !is_aiming) {
					right_press = true;
					std::shared_ptr<Comando> cmd;
					cmd = factory.accion_mover(GAME_MOVE_RIGHT);
					std::shared_ptr<Mensaje> msg = std::make_shared<Mensaje>(cmd);
					acciones.push(msg);
				} else if (tecla == SDLK_LEFT && !left_press && !is_aiming) {
					left_press = true;
					std::shared_ptr<Comando> cmd;
					cmd = factory.accion_mover(GAME_MOVE_LEFT);
					std::shared_ptr<Mensaje> msg = std::make_shared<Mensaje>(cmd);
					acciones.push(msg);
				} else if (tecla == SDLK_RETURN && !is_aiming && !return_press){
					// Quiere saltar hacia adelante
					return_press = true;
					// Enviar por protocolo comando "saltar adelante"
				} else if (tecla == SDLK_BACKSPACE && !is_aiming && !backspace_press){
					// Quere saltar hacia atras
					backspace_press = true;
					// Enviar por protocolo comando "saltar atras"
				} else if (tecla == SDLK_1 && !has_selected_weapon) {
					// Selecciono la Bazooka
					// ToDo: Desarrollar para cuenta regresiva
					has_selected_weapon = true;
					is_aiming = true;
					// Enviar comando "saco bazooka" por protocolo
				} else if (tecla == SDLK_2 && !has_selected_weapon) {
					// Selecciono el Bate
					// ToDo: Desarrollar para cuenta regresiva
					has_selected_weapon = true;
					// Enviar comando "saco bate" por protocolo
				} else if (tecla == SDLK_3 && !has_selected_weapon) {
					// Selecciono Teletransportacion
					// ToDo: Desarrollar para cuenta regresiva
					has_selected_weapon = true;
					// Enviar comando "saco teletransportador" por protocolo
				} else if (tecla == SDLK_4 && !has_selected_weapon) {
					// Selecciono la Dinamita
					// ToDo: Desarrollar para cuenta regresiva
					has_selected_weapon = true;
					// Enviar comando "saco dinamita" por protocolo
				} else if (tecla == SDLK_5 && !has_selected_weapon) {
					// Selecciono el Ataque Aereo
					// ToDo: Desarrollar para cuenta regresiva
					has_selected_weapon = true;
					// Enviar comando "saco ataque aereo" por protocolo
				} else if (tecla == SDLK_6 && !has_selected_weapon) {
					// Selecciono la Granada santa
					is_aiming = true;
					has_selected_weapon = true;
					// Enviar comando "saco granada santa" por protocolo
				} else if (tecla == SDLK_7 && !has_selected_weapon) {
					// Selecciono la Granada verde
					is_aiming = true;
					has_selected_weapon = true;
					// Enviar comando "saco granada verde" por protocolo
				} else if (tecla == SDLK_8 && !has_selected_weapon) {
					// Selecciono la Banana
					is_aiming = true;
					has_selected_weapon = true;
					// Enviar comando "saco banana" por protocolo
				} else if (tecla == SDLK_9 && !has_selected_weapon) {
					// Selecciono la Granada roja
					has_selected_weapon = true;
					is_aiming = true;
					// Enviar comando "saco granada roja" por protocolo
				} else if (tecla == SDLK_0 && !has_selected_weapon) {
					// Selecciono el mortero
					has_selected_weapon = true;
					is_aiming = true;
					// Enviar comando "saco mortero" por protocolo
				} else if (tecla == SDLK_UP && !up_press && is_aiming) {
					// Comienza a presionar arriba mientras esta apuntando
					up_press = true;
					// Enviar por protocolo que empezo a aumentar el angulo
				} else if (tecla == SDLK_DOWN && !down_press && is_aiming) {
					// Comienza a presionar abajo mientras esta apuntando
					down_press = true;
					// Enviar por protocolo que empezo a disminuir el rango
				} else if (tecla == SDLK_SPACE && has_selected_weapon && !is_charging_power) {
					// Esta cargando la potencia del arma, por lo que envio
					// Cuando la empieza a presionar y despues cuando la suelta
					is_charging_power = true;
					// Enviar comando empezo a cargar el poder por protocolo
				}
			} else if (event.type == SDL_KEYUP) {
				SDL_Keycode tecla = event.key.keysym.sym;
				if (tecla == SDLK_RIGHT) {
					right_press = false;
					std::shared_ptr<Comando> cmd;
					cmd = factory.accion_detener();
					std::shared_ptr<Mensaje> msg = std::make_shared<Mensaje>(cmd);
					acciones.push(msg);
				} else if (tecla == SDLK_LEFT) {
					left_press = false;
					std::shared_ptr<Comando> cmd;
					cmd = factory.accion_detener();
					std::shared_ptr<Mensaje> msg = std::make_shared<Mensaje>(cmd);
					acciones.push(msg);
				} else if (tecla == SDLK_UP) {
					up_press = false;
					// Enviar por protocolo que se dejo de aumentar el angulo
				} else if (tecla == SDLK_DOWN) {
					down_press = false;
					// Enviar por protocolo que se dejo de disminuir el angulo
				} else if (tecla == SDLK_SPACE) {
					is_charging_power = false;
					// Enviar por protocolo que disparó (que dejo de cargar el poder)
				} else if (tecla == SDLK_RETURN) {
					return_press = false;
				} else if (tecla == SDLK_BACKSPACE) {
					backspace_press = false;
				}
			}
        }
        
		// Obtengo el tamaño actual de la ventana
    	int window_width = renderer.GetOutputWidth();
		int window_height = renderer.GetOutputHeight();

		float x_scale = window_width / CAMERA_WIDTH;
		float y_scale = window_height / CAMERA_HEIGHT;

        // Limpio la pantalla
		renderer.Clear();

        //Saco una Snapshot de la Queue
        std::shared_ptr<Mensaje> snap = snapshots.pop();
		if (snap->tipo_comando == COMANDO::CMD_ENVIAR_SNAPSHOT){
			std::shared_ptr<Snapshot> snapshot = snap->snap;
			//Grafico la snapshot
			snapshot->apply_to_world(world);
			world.present(it, renderer, texture_manager, x_scale, y_scale);

		}
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