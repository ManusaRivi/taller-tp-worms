#include "game.h"
#include "camara.h"
#include "../comandos/mensajes/mensaje_handshake.h"
#include "../comandos/mensajes/mensaje_snapshot.h"
#include "../comandos/mensajes/mensaje_handshake_enviar.h"
using namespace SDL2pp;

#define GAME_MOVE_RIGHT 0x01
#define GAME_MOVE_LEFT 0x02

#define GAME_JUMP_FORWARD 0x01
#define GAME_JUMP_BACKWARDS	0x02

#define ANGULO_ARRIBA 0x00
#define ANGULO_ABAJO 0x01

#define BAZOOKA 5
#define BASEBALL 6
#define TELEPORTACION 8
#define DINAMITA 9
#define ATAQUE_AEREO 11
#define GRANADA_SANTA 12
#define GRANADA_VERDE 14
#define BANANA 16
#define GRANADA_ROHA 18
#define MORTERO 20

Game::Game(Queue<std::shared_ptr<MensajeCliente>> &queue, Queue<std::shared_ptr<MensajeCliente>> &acciones_):snapshots(queue), acciones(acciones_){}

int Game::run() try {
	std::shared_ptr<World> world;
	std::vector<uint32_t> id_gusanos;
	// uint32_t id_player;
	std::shared_ptr<SnapshotCliente> snapshot;

	
	bool se_recibieron_ids = false;
	while(!se_recibieron_ids){
		std::shared_ptr<MensajeCliente> msg = snapshots.pop();
		if (msg->get_tipo_comando() == COMANDO::CMD_HANDSHAKE){
			std::shared_ptr<MensajeHandshake> handshake = std::dynamic_pointer_cast<MensajeHandshake>(msg);
			id_gusanos = handshake->get_gusanos();
			// id_player = handshake->get_id();
			world = handshake->get_world();
			// std::shared_ptr<MensajeHandshakeEnviar> handshake_envaiar = std::make_shared<MensajeHandshakeEnviar>(id_player,id_gusanos);
			acciones.push(handshake);
			se_recibieron_ids = true;
			

			/*
				En el Handshake deberia recibir las posiciones de las vigas 
				Y las posiciones iniciales de todos los gusanos (como una snapshot,
				ahora la snapshot deberia dejar de contener las vigas)

				* Idea: Crear world en el protocolo de esta manera:
			
					World world(ancho_mapa, alto_mapa);
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

	// printf("El id del player es : %u \n", id_player);
	
	SDL_SetRelativeMouseMode(SDL_TRUE);

    // Inicializo SDL
	SDL sdl(SDL_INIT_VIDEO);
	// Inicializo SDL_ttf
	SDLTTF ttf;
	// Inicializo SDL_mixer
    //SDL2pp::Mixer mixer(MIX_DEFAULT_FREQUENCY, GAME_MIX_FORMAT, 2, 1024);

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

	// Reproduzco musica ambiente
	//Chunk musica_ambiente(PROJECT_SOURCE_DIR "./client/game/Sonidos/data/MusicaAmbiente.mp3");
	//mixer.PlayChannel(-1, musica_ambiente, 0);

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
	bool has_selected_weapon = false;
	bool is_aiming = false;
	bool is_charging_power = false;

	Camara camara = {0.0f, 0.0f};

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
				} else if (tecla == SDLK_RIGHT && !right_press) {
					if (is_aiming) {
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
					if (is_aiming) {
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
				} else if (tecla == SDLK_RETURN && !is_aiming && !return_press){
					// Quiere saltar hacia adelante
					return_press = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.saltar(GAME_JUMP_FORWARD);
					acciones.push(msg);
					// Enviar por protocolo comando "saltar adelante"
				} else if (tecla == SDLK_BACKSPACE && !is_aiming && !backspace_press){
					// Quere saltar hacia atras
					backspace_press = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.saltar(GAME_JUMP_BACKWARDS);
					acciones.push(msg);
					// Enviar por protocolo comando "saltar atras"
				} else if (tecla == SDLK_1 && !has_selected_weapon) {
					// Selecciono la Bazooka
					// ToDo: Desarrollar para cuenta regresiva
					has_selected_weapon = true;
					is_aiming = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(BAZOOKA);
					acciones.push(msg);
					// Enviar comando "saco bazooka" por protocolo
				} else if (tecla == SDLK_2 && !has_selected_weapon) {
					// Selecciono el Bate
					// ToDo: Desarrollar para cuenta regresiva
					has_selected_weapon = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(BASEBALL);
					acciones.push(msg);
					// Enviar comando "saco bate" por protocolo
				} else if (tecla == SDLK_3 && !has_selected_weapon) {
					// Selecciono Teletransportacion
					// ToDo: Desarrollar para cuenta regresiva
					has_selected_weapon = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(TELEPORTACION);
					acciones.push(msg);
					// Enviar comando "saco teletransportador" por protocolo
				} else if (tecla == SDLK_4 && !has_selected_weapon) {
					// Selecciono la Dinamita
					// ToDo: Desarrollar para cuenta regresiva
					has_selected_weapon = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(DINAMITA);
					acciones.push(msg);
					// Enviar comando "saco dinamita" por protocolo
				} else if (tecla == SDLK_5 && !has_selected_weapon) {
					// Selecciono el Ataque Aereo
					// ToDo: Desarrollar para cuenta regresiva
					has_selected_weapon = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(ATAQUE_AEREO);
					acciones.push(msg);
					// Enviar comando "saco ataque aereo" por protocolo
				} else if (tecla == SDLK_6 && !has_selected_weapon) {
					// Selecciono la Granada santa
					is_aiming = true;
					has_selected_weapon = true;
					// printf("Se manda una granada santa\n");
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(GRANADA_SANTA);
					acciones.push(msg);
					// Enviar comando "saco granada santa" por protocolo
				} else if (tecla == SDLK_7 && !has_selected_weapon) {
					// Selecciono la Granada verde
					is_aiming = true;
					has_selected_weapon = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(GRANADA_VERDE);
					acciones.push(msg);
					// Enviar comando "saco granada verde" por protocolo
				} else if (tecla == SDLK_8 && !has_selected_weapon) {
					// Selecciono la Banana
					is_aiming = true;
					has_selected_weapon = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(BANANA);
					acciones.push(msg);
					// Enviar comando "saco banana" por protocolo
				} else if (tecla == SDLK_9 && !has_selected_weapon) {
					// Selecciono la Granada roja
					has_selected_weapon = true;
					is_aiming = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(GRANADA_ROHA);
					acciones.push(msg);
					// Enviar comando "saco granada roja" por protocolo
				} else if (tecla == SDLK_0 && !has_selected_weapon) {
					// Selecciono el mortero
					has_selected_weapon = true;
					is_aiming = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_arma(MORTERO);
					acciones.push(msg);
					// Enviar comando "saco mortero" por protocolo
				} else if (tecla == SDLK_UP && !up_press && is_aiming) {
					// Comienza a presionar arriba mientras esta apuntando
					up_press = true;
					std::shared_ptr<MensajeCliente> msg = mensajes.cambiar_angulo(ANGULO_ARRIBA);
					acciones.push(msg);
					// Enviar por protocolo que empezo a aumentar el angulo
				} else if (tecla == SDLK_DOWN && !down_press && is_aiming) {
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
				if (tecla == SDLK_RIGHT && !is_aiming) {
					right_press = false;
					std::shared_ptr<MensajeCliente> msg = mensajes.detener_movimiento();
					acciones.push(msg);
				} else if (tecla == SDLK_LEFT && !is_aiming) {
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
					is_aiming = false;
					has_selected_weapon = false;
				} else if (tecla == SDLK_RETURN) {
					return_press = false;
				} else if (tecla == SDLK_BACKSPACE) {
					backspace_press = false;
				}
			} else if(event.type == SDL_MOUSEMOTION) {
				camara.x += event.motion.xrel;
                camara.y += event.motion.yrel;
			}
        }
        
		// Obtengo el tamaño actual de la ventana
    	int window_width = renderer.GetOutputWidth();
		int window_height = renderer.GetOutputHeight();

		//Obtengo la escala:
    	float x_scale = window_width / CAMERA_WIDTH;
		float y_scale = window_height / CAMERA_HEIGHT;

        // Limpio la pantalla
		renderer.Clear();

        //Saco una SnapshotCliente de la Queue
        std::shared_ptr<MensajeCliente> snap = snapshots.pop();
		if (snap->get_tipo_comando() == COMANDO::CMD_ENVIAR_SNAPSHOT){
			std::shared_ptr<MensajeSnapshot> msg = std::dynamic_pointer_cast<MensajeSnapshot>(snap);
			std::shared_ptr<SnapshotCliente> snapshot = msg->get_snap();
			snapshot->apply_to_world((*world));

			// PRUEBA PROYECTIL ----------------------------------------------------
			//Asi deberian agregarse por protocolo los proyectiles:
			float pos_x = 1.5f;
			float pos_y = 25.82f;
			float angle = 180.0f;
			unique_ptr<Projectile> prueba = ProjectileGenerator::get_proyectile_with_code(0, pos_x, pos_y, angle);
			(*world).add_projectile(std::move(prueba));
			//--------------------------------------------------------------------

			(*world).present(it_inc, renderer, texture_manager, x_scale, y_scale, camara);
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
    }


} catch (std::exception& e) {
	// En caso de error, lo imprimo y devuelvo 1.
	std::cerr << e.what() << std::endl;
	return 1;
}