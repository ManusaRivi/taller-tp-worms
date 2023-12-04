#include "world.h"
#include "camara.h"

using namespace SDL2pp;

World::World(float map_width, float map_height): camera_x(0), camera_y(0),
            proy_it(0), _map_width(map_width), _map_height(map_height) {
    
    for (int i= 0; i < 10; i++) {
        ammo[i] = 0;
    }

}

void World::add_worm(std::shared_ptr<Worm> worm, int id) {
    worms.emplace(id, worm);
}

void World::add_beam(Beam beam) {
    beams.push_back(beam);
}

void World::add_sound(int sound) {
    sonidos.push_back(sound);
}

void World::add_projectile(std::unique_ptr<ProjectileClient> projectile) {
    projectiles.emplace(projectile->get_id(), std::move(projectile));
}

void World::add_explosion(ExplosionCliente explosion) {
    explosions.emplace(explosion.get_id(), explosion);
}

void World::add_provision(ProvisionClient provision) {
    provisiones.emplace(provision.get_id(), provision);
}

void World::update_camera(int id_camera) {
    _id_camera = id_camera;
}

void World::update_turn(uint32_t id_actual_turn) {
    _id_actual_turn = id_actual_turn;
}

uint32_t World::get_turn() {
    return _id_actual_turn;
} 

void World::update_worm(const int& id, std::shared_ptr<Worm> worm) {
    worms.at(id)->update(std::move(worm));
}

void World::present_background(Renderer& renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale,
                        float& camera_x,
                        float& camera_y) {
    
    // Busco textura
    std::string texture_name("Background");
    Texture& background_tex = texture_manager.get_texture(texture_name);
    
    // Encuentro posicion relativa (esta en el (0, alto_mapa))
    float pos_rel_x = 0 - camera_x;
    float pos_rel_y = 0 - camera_y;

    //Grafico
    background_tex.SetAlphaMod(255); // El fondo es totalmente opaco
    renderer.Copy(
				background_tex,
				Rect(0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT), // El sprite
				Rect(static_cast<int>(pos_rel_x * x_scale),
					static_cast<int>(pos_rel_y * y_scale),
					_map_width * x_scale, _map_height * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}

void World::present_water(
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale,
                        float& camera_x,
                        float& camera_y
                        ) {

    std::string texture_name_water("Agua");
    Texture& water_tex = texture_manager.get_texture(texture_name_water);

    float pos_rel_x = 0 - camera_x;
    float pos_rel_y = _map_height - WATER_HEIGHT - camera_y;

    //Grafico
    water_tex.SetAlphaMod(255); // Wl agua es totalmente opaca
    renderer.Copy(water_tex,
				Rect(0, 0, WATER_SPRITE_WIDTH, WATER_SPRITE_HEIGHT), // El sprite
				Rect(static_cast<int>(pos_rel_x * x_scale),
					static_cast<int>(pos_rel_y * y_scale),
					_map_width * x_scale, WATER_HEIGHT * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}

void World::present_hud(Renderer& renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale) {
    
    int ancho_hud = renderer.GetOutputWidth() / 2;
    int alto_hud = HUD_SPRITE_HEIGHT * ancho_hud / HUD_SPRITE_WIDTH;
    // Busco textura
    std::string texture_name("HUDWeapons");
    Texture& hud_tex = texture_manager.get_texture(texture_name);

    //Grafico
    hud_tex.SetAlphaMod(255); // El HUD es totalmente opaco
    renderer.Copy(hud_tex,
				Rect(0, 0, HUD_SPRITE_WIDTH, HUD_SPRITE_HEIGHT), // El sprite
				Rect(0, 0, ancho_hud, alto_hud), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
    
    present_weapon_power(renderer, texture_manager, x_scale, y_scale);
    if (has_timer) present_timer(renderer, texture_manager, x_scale, y_scale);
    present_ammo(renderer, texture_manager, x_scale, y_scale);
}

void World::present_weapon_power(Renderer& renderer,
                            TextureManager& texture_manager,
                            float& x_scale,
                            float& y_scale) {
    SDL_Rect power;
    SDL_Rect border;
	border.w = renderer.GetOutputWidth()/2 - 1*x_scale;
	border.h = POWER_HEIGHT * y_scale;
	border.x = renderer.GetOutputWidth()/2 + x_scale;
	border.y = 0;

    power.w = (renderer.GetOutputWidth()/2 - 1*x_scale)* weapon_power / MAX_POWER ;
	power.h = 1*y_scale;
	power.x = renderer.GetOutputWidth()/2 + x_scale;
	power.y = 0;

	SDL_Color power_color = {255, 0, 0, 255};
    SDL_Color border_color = {255, 255, 255, 255};

    SDL_SetRenderDrawColor(renderer.Get(), power_color.r, power_color.g, power_color.b, power_color.a);
	SDL_RenderFillRect(renderer.Get(), &power);

    // Dibuja el borde
	SDL_SetRenderDrawColor(renderer.Get(), border_color.r, border_color.g, border_color.b, border_color.a);
	SDL_RenderDrawRect(renderer.Get(), &border);
}

void World::present_timer(Renderer& renderer,
                            TextureManager& texture_manager,
                            float& x_scale,
                            float& y_scale) {
    std::string texture_name = "Explosion " + std::to_string(timer);
    Texture& text_texture = texture_manager.get_texture(texture_name);

    renderer.Copy(text_texture, NullOpt, 
                    Rect(renderer.GetOutputWidth()/2 + x_scale,
                        2*y_scale,
                        text_texture.GetWidth() * 0.04 * x_scale,
                        text_texture.GetHeight() * 0.04 * y_scale));
}

void World::present_sight(Renderer& renderer,
                            TextureManager& texture_manager,
                            float& pos_x,
                            float& pos_y,
                            float& x_scale,
                            float& y_scale,
                            float& camera_x,
                            float& camera_y) {
    // Busco textura
    std::string texture_name("Sight");
    Texture& sight_tex = texture_manager.get_texture(texture_name);

    float pos_rel_x = pos_x - camera_x;
    float pos_rel_y = _map_height - pos_y - camera_y;

    //Grafico
    sight_tex.SetAlphaMod(255);
    renderer.Copy(sight_tex,
				Rect(0, 0, SIGHT_SPRITE_DIAMETER, SIGHT_SPRITE_DIAMETER), // El sprite
				Rect(static_cast<int>((pos_rel_x - SIGHT_DIAMETER * 0.5) * x_scale),
                        static_cast<int>((pos_rel_y - SIGHT_DIAMETER * 0.5) * y_scale),
                        SIGHT_DIAMETER * x_scale, SIGHT_DIAMETER * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}

void World::present_ammo(Renderer& renderer,
                         TextureManager& texture_manager,
                         float& x_scale,
                         float& y_scale) {
    TTF_Font* font = TTF_OpenFont(PROJECT_SOURCE_DIR "/client/game/Texturas/data/Vera.ttf", 24);

    SDL_Color ammoColor = {255, 255, 255, 255};
    SDL_Color back_color = {0, 0, 0, 255};

    std::vector<SDL_Texture*> textTextures;
    std::vector<SDL_Rect> textRects;
    for (int i = 0; i < 10; i++) {
        std::string am = std::to_string(ammo[i]);
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, am.c_str(), ammoColor);

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer.Get(), textSurface);
        SDL_FreeSurface(textSurface);

        textTextures.push_back(textTexture);

        SDL_Rect textRect;
        textRect.w = static_cast<int>(textSurface->w * 0.02 * x_scale);
        textRect.h = static_cast<int>(textSurface->h * 0.02 * y_scale);
        textRect.x = static_cast<int>(i * 1.635 * x_scale + 0.1 * x_scale);
        textRect.y = static_cast<int>(0.1 * y_scale);

        textRects.push_back(textRect);
    }

    for (size_t i = 0; i < textTextures.size(); i++) {
        SDL_Rect back;
        back.w = textRects[i].w;
        back.h = textRects[i].h;
        back.x = textRects[i].x;
        back.y = textRects[i].y;

        SDL_SetRenderDrawColor(renderer.Get(), back_color.r, back_color.g, back_color.b, back_color.a);
        SDL_RenderFillRect(renderer.Get(), &back);

        SDL_RenderCopy(renderer.Get(), textTextures[i], nullptr, &textRects[i]);
    }

    // Liberar recursos
    TTF_CloseFont(font);

    // Limpiar texturas
    for (SDL_Texture* texture : textTextures) {
        SDL_DestroyTexture(texture);
    }
}


void World::present(int& it_inc,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        SoundManager& sound_manager,
                        Mixer& mixer,
                        float& x_scale,
                        float& y_scale,
                        Camara& camara){
    
    int window_width = renderer.GetOutputWidth();
    int window_height = renderer.GetOutputHeight();

    // Obtengo la posicion de la camara:
    float pos_foco_x = 0;
    float pos_foco_y = 0;
    
    auto it_worm = worms.find(_id_camera);
    auto it_proj = projectiles.find(_id_camera);
    auto it_exp = explosions.find(_id_camera);

    if (it_worm != worms.end()) {
        pos_foco_x = it_worm->second->get_x();
        pos_foco_y = it_worm->second->get_y();
    } else if (it_proj != projectiles.end()){
        pos_foco_x = it_proj->second->get_x();
        pos_foco_y = it_proj->second->get_y();
    } else if (it_exp != explosions.end()) {
        pos_foco_x = it_exp->second.get_x();
        pos_foco_y = it_exp->second.get_y();
    }

    camera_x = pos_foco_x - (window_width / (2 * x_scale)) + camara.x;
    camera_y = _map_height - (pos_foco_y + (window_height / (2 * y_scale))) + camara.y;

    if (camera_x < 0) camera_x = 0;
    if (camera_x > _map_width - (window_width / x_scale)) camera_x = _map_width - (window_width / x_scale);
    if (camera_y > _map_height - (window_height / y_scale)) camera_y = _map_height - (window_height / y_scale);
    if (camera_y < 0) camera_y = 0;

    // Grafico fondo
    present_background(renderer, texture_manager, x_scale, y_scale, camera_x, camera_y);

    // Grafico vigas
    for (auto& beam : beams) {
        beam.present(renderer, texture_manager, _map_height, x_scale, y_scale, camera_x, camera_y);
    }

    // Grafico gusanos
    for (auto& worm : worms) {
        worm.second->present(it_inc, renderer, texture_manager, _map_height, x_scale, y_scale, camera_x, camera_y);
    }

    //present_water(renderer, texture_manager, x_scale, y_scale, camera_x, camera_y);

    // Grafico proyectiles
    proy_it += it_inc;
    for (auto& projectil : projectiles) {
        projectil.second->present(proy_it, renderer, texture_manager, _map_height, x_scale, y_scale, camera_x, camera_y);
    }
    projectiles.clear();

    // Grafico provisiones
    for (auto& provision : provisiones) {
        if(provision.second.get_estado() == 0) {
            provision.second.present(proy_it, renderer, texture_manager, _map_height, x_scale, y_scale, camera_x, camera_y);
        }
    }
    provisiones.clear();

    // Grafico Explosiones
    for (auto& explosion : explosions) {
        explosion.second.present(it_inc, renderer, texture_manager, _map_height, x_scale, y_scale, camera_x, camera_y);
    }

    // Borro las explosiones que ya no existen
    for (auto it = explosions.begin(); it != explosions.end();) {
        if (it->second.is_finished()) {
            it = explosions.erase(it);
        } else {
            ++it;
        }
    }

    // Grafico HUD
    present_hud(renderer, texture_manager, x_scale, y_scale);

    // Grafico mira
    if (has_tp) present_sight(renderer, texture_manager, tp_x, tp_y, x_scale, y_scale, camera_x, camera_y);
    else if (has_air_attack) present_sight(renderer, texture_manager, air_attack_x, air_attack_y, x_scale, y_scale, camera_x, camera_y);

    // Reproduzco sonidos
    while (!sonidos.empty()) {
        std::shared_ptr<Chunk> sonido = sound_manager.get_sound(sonidos.back());
        mixer.PlayChannel(-1, (*sonido), 0);
        sonidos.pop_back();
    }

    renderer.Present();
}

float World::get_camera_x() {
    return camera_x;
}

float World::get_camera_y() {
    return camera_y;
}

float World::get_map_height() {
    return _map_height;
}

std::vector<Beam> World::get_beams(){
    return this->beams;
}
std::map<int, std::shared_ptr<Worm>> World::get_worms(){
    return this->worms;
}

bool World::checkOnePlayerRemains() {
    
    bool pertenecen_al_mismo_equipo = true;
    uint32_t equipo_comun = worms.begin()->second->getEquipo();

    for (const auto& par : worms) {
        if ((par.second->getEquipo() != equipo_comun) && (par.second->getVida() > 0)) {
            pertenecen_al_mismo_equipo = false;
            break;
        }
    }

    return pertenecen_al_mismo_equipo;
}

void World::set_weapon_power(int& power) {
    weapon_power = power;
}

void World::set_tp(bool& _has_tp, float& pos_x, float& pos_y) {
    has_tp = _has_tp;
    tp_x = pos_x;
    tp_y = pos_y;
}

void World::set_air_attack(bool& _has_air_attack, float& pos_x, float& pos_y) {
    has_air_attack = _has_air_attack;
    air_attack_x = pos_x;
    air_attack_y = pos_y;
}
void World::set_timer(bool& _has_timer, int& _timer) {
    has_timer = _has_timer;
    timer = _timer;
}

void World::set_ammo(const int& weapon, const int& _ammo) {
    ammo[weapon] = _ammo;
}