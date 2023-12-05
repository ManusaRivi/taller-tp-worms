#include "game.h"
#include "camara.h"
#include "../comandos/mensajes/mensaje_handshake.h"
#include "../comandos/mensajes/mensaje_snapshot.h"
#include "../comandos/mensajes/mensaje_handshake_enviar.h"
#include "../comandos/mensajes/mensaje_partida_termino.h"
using namespace SDL2pp;

#define GAME_MOVE_RIGHT 0x01
#define GAME_MOVE_LEFT 0x02

#define GAME_JUMP_FORWARD 0x01
#define GAME_JUMP_BACKWARDS	0x02

#define ANGULO_ARRIBA 0x00
#define ANGULO_ABAJO 0x01

Game::Game(Queue<std::shared_ptr<MensajeCliente>> &queue, Queue<std::shared_ptr<MensajeCliente>> &acciones_):snapshots(queue), acciones(acciones_) {
	this->is_active = true;
}

int Game::run() try {
	std::shared_ptr<World> world;
	std::vector<uint32_t> id_gusanos;
	std::shared_ptr<SnapshotCliente> snapshot;

	
	bool se_recibieron_ids = false;
	while(!se_recibieron_ids){
		std::shared_ptr<MensajeCliente> msg = snapshots.pop();
		if (msg->get_tipo_comando() == COMANDO::CMD_HANDSHAKE){
			std::shared_ptr<MensajeHandshake> handshake = std::dynamic_pointer_cast<MensajeHandshake>(msg);
			id_gusanos = handshake->get_gusanos();
			world = handshake->get_world();
			acciones.push(handshake);
			se_recibieron_ids = true;
		}
	}
	
	SDL_SetRelativeMouseMode(SDL_TRUE);

    // Inicializo SDL
	SDL sdl(SDL_INIT_VIDEO);
	// Inicializo SDL_ttf
	SDLTTF ttf;
	// Inicializo SDL_mixer
    SDL2pp::Mixer mixer(MIX_DEFAULT_FREQUENCY, GAME_MIX_FORMAT, 2, 1024);
	Mix_Volume(-1, MIX_MAX_VOLUME * 0.6);
	Mix_AllocateChannels(30);
    // Creo la ventana: 
    // Dimensiones: 854x480, redimensionable
    // Titulo: Worms
	Window window("Worms",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			854, 480,
			SDL_WINDOW_RESIZABLE);

    // Creo un renderizador default
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Cargo las texturas
    TextureManager texture_manager(renderer);

	// Cargo los sonidos
	SoundManager sound_manager;

	// Reproduzco musica ambiente
	std::shared_ptr<Chunk> musica_ambiente = sound_manager.get_sound(SoundTypes::AMBIENT_MUSIC);
	mixer.PlayChannel(-1, (*musica_ambiente), 0);

	// Tomo el tiempo actual
    unsigned int t1 = SDL_GetTicks();

	// Numero de frame de la iteracion de las animaciones
	int it_inc = 0;

	//Variables de teclas:
	bool right_press = false;
	bool left_press = false;
	bool up_press = false;
	bool down_press = false;
	bool return_press = false;
	bool backspace_press = false;
	bool is_charging_power = false;

	bool has_selected_weapon = false;
	bool mouse_weapon = false;

	Camara camara = {0.0f, 0.0f};

    // Loop principal
	while (is_active) {

		// Obtengo el tamaño actual de la ventana
    	int window_width = renderer.GetOutputWidth();
		int window_height = renderer.GetOutputHeight();

		//Obtengo la escala:
    	float x_scale = window_width / CAMERA_WIDTH;
		float y_scale = window_height / CAMERA_HEIGHT;


		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				SDL_Keycode tecla = event.key.keysym.sym;
				if (tecla == SDLK_ESCAPE){
					return 0;
				} else if(tecla == SDLK_c) {
					std::shared_ptr<MensajeCliente> msg = mensajes.activar_cheat(Cheats::SETEAR_VIDA_A_1);
					acciones.push(msg);
				} else if(tecla == SDLK_v) {
					std::shared_ptr<MensajeCliente> msg = mensajes.activar_cheat(Cheats::SUPER_VELOCIDAD);
					acciones.push(msg);
				} else if(tecla == SDLK_b) {
					std::shared_ptr<MensajeCliente> msg = mensajes.activar_cheat(Cheats::SUPER_SALTO);
					acciones.push(msg);
				} else if (tecla == SDLK_RIGHT && !right_press) {
					if (has_selected_weapon) {
						// Quiere mirar a la derecha mientras apunta
						// Enviar por protocolo "mirar a la derecha apuntando" (es cambiar el 
						// lado para el cual mira si antes miraba a la izquierda)
						std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_direccion_arma(GAME_MOVE_RIGHT);
						acciones.push(msg);
					} else {
						right_press = true;
						std::shared_ptr<MensajeCliente> msg = mensajes.moverse(GAME_MOVE_RIGHT);
						acciones.push(msg);
					}
				} else if (tecla == SDLK_LEFT && !left_press) {
					if (has_selected_weapon) {
						// Quiere mirar a la izquierda mientras apunta
						// Enviar por protocolo "mirar a la izquierda apuntando" (es cambiar el 
						// lado para el cual mira si antes miraba a la derecha)
						std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_direccion_arma(GAME_MOVE_LEFT);
						acciones.push(msg);
					} else {
						left_press = true;
						std::shared_ptr<MensajeCliente> msg = mensajes.moverse(GAME_MOVE_LEFT);
						acciones.push(msg);
					}
				} else if (tecla == SDLK_RETURN && !has_selected_weapon && !return_press){
					// Quiere saltar hacia adelante
					return_press = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.saltar(GAME_JUMP_FORWARD);
					acciones.push(msg);
					// Enviar por protocolo comando "saltar adelante"
				} else if (tecla == SDLK_BACKSPACE && !has_selected_weapon && !backspace_press){
					// Quere saltar hacia atras
					backspace_press = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.saltar(GAME_JUMP_BACKWARDS);
					acciones.push(msg);
					// Enviar por protocolo comando "saltar atras"
				} else if (tecla == SDLK_1 && !left_press && !right_press) {
					if (has_selected_weapon) {
						std::shared_ptr<MensajeCliente> msg = mensajes.setear_timer(1);
						acciones.push(msg);
					} else {
						// Selecciono la Bazooka
						// ToDo: Desarrollar para cuenta regresiva
						has_selected_weapon = true;
						std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(Armas::BAZOOKA);
						acciones.push(msg);
					// Enviar comando "saco bazooka" por protocolo
					}
				} else if (tecla == SDLK_2 && !left_press && !right_press) {
					if (has_selected_weapon) {
						std::shared_ptr<MensajeCliente> msg = mensajes.setear_timer(2);
						acciones.push(msg);
					} else {
						// Selecciono el Bate
						// ToDo: Desarrollar para cuenta regresiva
						has_selected_weapon = true;
						std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(Armas::BATE);
						acciones.push(msg);
						// Enviar comando "saco bate" por protocolo
					}
				} else if (tecla == SDLK_3 && !left_press && !right_press) {
					if (has_selected_weapon) {
						std::shared_ptr<MensajeCliente> msg = mensajes.setear_timer(3);
						acciones.push(msg);
					} else {
						// Selecciono Teletransportacion
						// ToDo: Desarrollar para cuenta regresiva
						has_selected_weapon = true;
						mouse_weapon = true;
						std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(Armas::TELETRANSPORTACION);
						acciones.push(msg);
						// Enviar comando "saco teletransportador" por protocolo
					}
				} else if (tecla == SDLK_4 && !left_press && !right_press) {
					if (has_selected_weapon) {
						std::shared_ptr<MensajeCliente> msg = mensajes.setear_timer(4);
						acciones.push(msg);
					} else {
						// Selecciono la Dinamita
						// ToDo: Desarrollar para cuenta regresiva
						has_selected_weapon = true;
						std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(Armas::DINAMITA);
						acciones.push(msg);
						// Enviar comando "saco dinamita" por protocolo
					}
				} else if (tecla == SDLK_5 && !left_press && !right_press) {
					if (has_selected_weapon) {
						std::shared_ptr<MensajeCliente> msg = mensajes.setear_timer(5);
						acciones.push(msg);
					} else {
						// Selecciono el Ataque Aereo
						// ToDo: Desarrollar para cuenta regresiva
						has_selected_weapon = true;
						mouse_weapon = true;
						std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(Armas::ATAQUE_AEREO);
						acciones.push(msg);
						// Enviar comando "saco ataque aereo" por protocolo
					}
				} else if (tecla == SDLK_6 && !has_selected_weapon && !left_press && !right_press) {
					// Selecciono la Granada santa
					has_selected_weapon = true;
					// printf("Se manda una granada santa\n");
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(Armas::GRANADA_SANTA);
					acciones.push(msg);
					// Enviar comando "saco granada santa" por protocolo
				} else if (tecla == SDLK_7 && !has_selected_weapon && !left_press && !right_press) {
					// Selecciono la Granada verde
					has_selected_weapon = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(Armas::GRANADA_VERDE);
					acciones.push(msg);
					// Enviar comando "saco granada verde" por protocolo
				} else if (tecla == SDLK_8 && !has_selected_weapon && !left_press && !right_press) {
					// Selecciono la Banana
					has_selected_weapon = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(Armas::BANANA);
					acciones.push(msg);
					// Enviar comando "saco banana" por protocolo
				} else if (tecla == SDLK_9 && !has_selected_weapon && !left_press && !right_press) {
					// Selecciono la Granada roja
					has_selected_weapon = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(Armas::GRANADA_ROJA);
					acciones.push(msg);
					// Enviar comando "saco granada roja" por protocolo
				} else if (tecla == SDLK_0 && !has_selected_weapon && !left_press && !right_press) {
					// Selecciono el mortero
					has_selected_weapon = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(Armas::MORTERO);
					acciones.push(msg);
					// Enviar comando "saco mortero" por protocolo
				} else if (tecla == SDLK_UP && !up_press && has_selected_weapon) {
					// Comienza a presionar arriba mientras esta apuntando
					up_press = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_angulo(ANGULO_ARRIBA);
					acciones.push(msg);
					// Enviar por protocolo que empezo a aumentar el angulo
				} else if (tecla == SDLK_DOWN && !down_press && has_selected_weapon) {
					// Comienza a presionar abajo mientras esta apuntando
					down_press = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_angulo(ANGULO_ABAJO);
					acciones.push(msg);
					// Enviar por protocolo que empezo a disminuir el rango
				} else if (tecla == SDLK_SPACE && has_selected_weapon && !is_charging_power) {
					// Esta cargando la potencia del arma, por lo que envio
					// Cuando la empieza a presionar y despues cuando la suelta
					is_charging_power = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cargar_arma();
					acciones.push(msg);
					// Enviar comando empezo a cargar el poder por protocolo
				}
				camara.x = 0;
				camara.y = 0;
			} else if (event.type == SDL_KEYUP) {
				SDL_Keycode tecla = event.key.keysym.sym;
				camara.x = 0;
				camara.y = 0;
				if (tecla == SDLK_RIGHT && !has_selected_weapon) {
					right_press = false;
					std::shared_ptr<MensajeCliente> msg = mensajes.detener_movimiento();
					acciones.push(msg);
				} else if (tecla == SDLK_LEFT && !has_selected_weapon) {
					left_press = false;
					std::shared_ptr<MensajeCliente> msg = mensajes.detener_movimiento();
					acciones.push(msg);
				} else if (tecla == SDLK_UP) {
					up_press = false;
					std::shared_ptr<MensajeCliente> msg = mensajes.detener_angulo();
					acciones.push(msg);
					// Enviar por protocolo que se dejo de aumentar el angulo
				} else if (tecla == SDLK_DOWN) {
					down_press = false;
					std::shared_ptr<MensajeCliente> msg = mensajes.detener_angulo();
					acciones.push(msg);
					// Enviar por protocolo que se dejo de disminuir el angulo
				} else if (tecla == SDLK_SPACE) {
					is_charging_power = false;
					std::shared_ptr<MensajeCliente> msg = mensajes.disparar();
					acciones.push(msg);
					// Enviar por protocolo que disparó (que dejo de cargar el poder)
					has_selected_weapon = false;
				} else if (tecla == SDLK_RETURN) {
					return_press = false;
				} else if (tecla == SDLK_BACKSPACE) {
					backspace_press = false;
				}
			} else if(event.type == SDL_MOUSEMOTION) {
    			if (event.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
					float mov_x = event.motion.xrel/2;
					float mov_y = event.motion.yrel/2;
    				camara.x += mov_x;
    				camara.y += mov_y;
				}
			} else if (event.type == SDL_MOUSEBUTTONDOWN) {
				SDL_MouseButtonEvent mouse_event = event.button;
				if (mouse_event.button == SDL_BUTTON_LEFT && has_selected_weapon && mouse_weapon) {
					int mouse_rel_x = mouse_event.x;
					int mouse_rel_y = mouse_event.y;
					float mouse_x = 0.0;
					float mouse_y = 0.0;
					get_mouse_position(mouse_rel_x, mouse_rel_y, x_scale, y_scale, (*world), mouse_x, mouse_y);
					std::shared_ptr<MensajeCliente> msg = mensajes.setear_target(mouse_x, mouse_y);
					acciones.push(msg);
				}
			}
        }

        // Limpio la pantalla
		renderer.Clear();

        //Saco una SnapshotCliente de la Queue
        std::shared_ptr<MensajeCliente> snap = snapshots.pop();
		if(snap->get_tipo_comando() == COMANDO::CMD_PARTIDA_TERMINADA){
			std::shared_ptr<MensajePartidaTermino> msg = std::dynamic_pointer_cast<MensajePartidaTermino>(snap);
			drawGameOverScreen(renderer, msg->get_equipo_ganador(),msg->fue_empate_());
			return 0;
		}
		if (snap->get_tipo_comando() == COMANDO::CMD_ENVIAR_SNAPSHOT){
			std::shared_ptr<MensajeSnapshot> msg = std::dynamic_pointer_cast<MensajeSnapshot>(snap);
			std::shared_ptr<SnapshotCliente> snapshot = msg->get_snap();
			if (snapshot->turn_change((*world)) || snapshot->not_ammo()) {
				has_selected_weapon = false;
				mouse_weapon = false;
			}
			snapshot->apply_to_world((*world));
			(*world).present(it_inc, renderer, texture_manager, sound_manager, mixer, x_scale, y_scale, camara);
			//snapshot->present(it_inc, renderer, texture_manager, window_width, window_height, x_scale, y_scale);
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
			it_inc = int(lost / FRAME_RATE);
			//it_inc += int(lost / FRAME_RATE);
		}

        // Limitador de frames: Duermo el programa durante un tiempo para no consumir
        // El 100% del CPU.
		SDL_Delay(rest);
		t1 += FRAME_RATE;
		it_inc = 1;
		//it_inc += 1;

		//Verifica si la partida termino
		// if(world->checkOnePlayerRemains()) {
		// 	this->is_active = false;
		// 	this->drawGameOverScreen(renderer);
		// }

    }


	return 0;

} catch (std::exception& e) {
	// En caso de error, lo imprimo y devuelvo 1.
	std::cerr << e.what() << std::endl;
	return 1;
}

void Game::get_mouse_position(int& mouse_rel_x, int& mouse_rel_y, float& scale_x,
                            float& scale_y, World& world, float& mouse_x, float& mouse_y) {
	
	mouse_x = (mouse_rel_x / scale_x) + world.get_camera_x();
	mouse_y = world.get_map_height() - ((mouse_rel_y / scale_y) + world.get_camera_y());
}


void Game::drawGameOverScreen(Renderer& renderer, uint32_t equipo_ganador, bool fue_empate) {
	std::string text;
	if(fue_empate){
		text = "Empate";
	}
	else{
		text = "Ganador: Equipo " + std::to_string(equipo_ganador);
	}
	TTF_Font* font = TTF_OpenFont("/var/worms/resources/Vera.ttf", 24);

	renderer.Clear();

	SDL_Rect back;

    back.w = renderer.GetOutputWidth();
	back.h = renderer.GetOutputHeight();
	back.x = 0;
	back.y = 0;

	SDL_Color back_color = {0, 0, 0, 255};

    SDL_SetRenderDrawColor(renderer.Get(), back_color.r, back_color.g, back_color.b, back_color.a);
	SDL_RenderFillRect(renderer.Get(), &back);

    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer.Get(), textSurface);

    SDL_Rect textRect;
    textRect.x = (renderer.GetOutputWidth() - textSurface->w) / 2;
    textRect.y = (renderer.GetOutputHeight() - textSurface->h) / 2;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    SDL_RenderCopy(renderer.Get(), textTexture, nullptr, &textRect);

    renderer.Present();

    SDL_Delay(3000);
}
