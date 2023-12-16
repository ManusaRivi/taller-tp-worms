#include "snapshot.h"

SnapshotCliente::SnapshotCliente(int id_camera): _id_camera(id_camera) {}


void SnapshotCliente::add_worm(std::shared_ptr<Worm> worm, int id) {
    worms.emplace(id, worm);
}

void SnapshotCliente::add_beam(Beam beam) {
    beams.push_back(beam);
}

void SnapshotCliente::add_projectile(std::unique_ptr<ProjectileClient> proyectil){
    projectiles.push_back(std::move(proyectil));
}

void SnapshotCliente::add_provision(ProvisionClient provision) {
    provisiones.push_back(provision);
}

void SnapshotCliente::add_sound(int sound) {
    sonidos.push_back(sound);
}

void SnapshotCliente::add_explosion(ExplosionCliente explosion){
    explosiones.push_back(explosion);
}

void SnapshotCliente::set_weapon_power(int& power) {
    weapon_power = power;
}

void SnapshotCliente::set_tp(bool& _has_tp, float& pos_x, float& pos_y) {
    has_tp = _has_tp;
    tp_x = pos_x;
    tp_y = pos_y;
}

void SnapshotCliente::set_not_ammo_weapon(bool& could_change_weapon) {
    not_ammo_weapon = !could_change_weapon;
}

bool SnapshotCliente::not_ammo() {
    return not_ammo_weapon;
}

void SnapshotCliente::set_air_attack(bool& _has_air_attack, float& pos_x, float& pos_y) {
    has_air_attack = _has_air_attack;
    air_attack_x = pos_x;
    air_attack_y = pos_y;
}
void SnapshotCliente::set_timer(bool& _has_timer, int& _timer) {
    has_timer = _has_timer;
    timer = _timer;
}

void SnapshotCliente::set_ammo(int& weapon, int& _ammo) {
    ammo[weapon] = _ammo;
}

void SnapshotCliente::set_wind(bool& wind_left, float& wind) {
    _wind_left = wind_left;
    _wind = wind;
}

void SnapshotCliente::apply_to_world(World& world) {
    // Actualizo camara
    world.update_camera(_id_camera);
    // Actualizo el turno
    world.update_turn(id_turno_actual);
    // Actualizo gusanos
    for (const auto& pair: worms) {
        world.update_worm(pair.first, std::move(pair.second));
    }
    // Actualizo proyectiles
    for(auto &c:projectiles){
        world.add_projectile(std::move(c));
    }
    // Actualizo explosiones
    for (auto& e: explosiones) {
        world.add_explosion(e);
    }
    // Actualizo provisiones
    for (auto& p: provisiones) {
        world.add_provision(p);
    }
    // Actualizo sonidos
    while (!sonidos.empty()) {
        world.add_sound(sonidos.back());
        sonidos.pop_back();
    }
    // Actualizo datos especiales
    world.set_weapon_power(weapon_power);
    world.set_tp(has_tp, tp_x, tp_y);
    world.set_air_attack(has_air_attack, air_attack_x, air_attack_y);
    world.set_timer(has_timer, timer);
    
    // Actualizo municion
    for (auto& pair: ammo) {
        world.set_ammo(pair.first, pair.second);
    }

    // Actualizo viento
    world.update_wind(_wind_left, _wind);
}

bool SnapshotCliente::turn_change(World& world) {
    return id_turno_actual != world.get_turn();
}

void SnapshotCliente::agregar_turno_actual(uint32_t turno){
    this->id_turno_actual = turno;
}

void SnapshotCliente::imprimir_posiciones(){
    for (auto &worm : worms){
        printf("La posicion x es = %f\n",worm.second->get_x());
    }
}

std::map<int, std::shared_ptr<Worm>> SnapshotCliente::get_worms(){
    return this->worms;
}

void SnapshotCliente::actulizar_camara(uint32_t id){
    this->_id_camera = id;
}

std::map<int,int> SnapshotCliente::get_municiones(){
    return this->ammo;
}

std::vector<std::pair<uint8_t,std::vector<float>>> SnapshotCliente::get_datos_especiales(){
    std::vector<std::pair<uint8_t,std::vector<float>>> dat;
    dat.push_back(std::pair<uint8_t,std::vector<float>>({has_tp,{tp_x,tp_y}}));
    dat.push_back(std::pair<uint8_t,std::vector<float>>({has_air_attack,{air_attack_x,air_attack_y}}));
    dat.push_back(std::pair<uint8_t,std::vector<float>>({has_timer,{static_cast<float>(timer)}}));
    return dat;
}

std::vector<std::unique_ptr<ProjectileClient>>& SnapshotCliente::get_proyectiles(){
    return this->projectiles;
}