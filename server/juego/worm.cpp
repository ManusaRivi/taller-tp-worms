#include "worm.h"

union BodyUserData {
    Worm* worm;
    // Otros tipos de datos que puedas necesitar.
};

Worm::Worm(b2World& world, int hitPoints, int direction, float x_pos, float y_pos, uint32_t id_) : 
            Colisionable(bodyType::WORM), coleccionArmas(std::make_unique<ColeccionArmas>(world)),
            armaActual(nullptr), facingDirection(direction), status(WormStates::IDLE), id(id_),
            angulo_disparo(0.0f), hitPoints(hitPoints), maxHealth(hitPoints), numBeamContacts(0),
            initialHeight(0.0f), finalHeight(0.0f), jumping(false), airborne(false), moving(false),
            apuntando(false), tomoDmgEsteTurno(false), x_target(0), y_target(0),pudo_cambiar_de_arma(true),
            super_velocidad(false), super_salto(false)
{
    b2BodyDef gusanoDef;
    gusanoDef.type = b2_dynamicBody;
    gusanoDef.position.Set(x_pos, y_pos);

    BodyUserData userData;
    userData.worm = this;
    gusanoDef.userData.pointer = reinterpret_cast<uintptr_t>(userData.worm);

    b2Body *gusano = world.CreateBody(&gusanoDef);
    this->body = gusano;
    

    b2PolygonShape gusanoBox;
    gusanoBox.SetAsBox(BOX_WIDTH, BOX_HEIGHT);

    b2FixtureDef fixtureGusano;
    fixtureGusano.shape = &gusanoBox;
    fixtureGusano.density = WORM_DENSITY;
    fixtureGusano.friction = WORM_FRICTION;
    fixtureGusano.restitution = WORM_RESTITUTION;
    fixtureGusano.restitutionThreshold = WORM_RESTITUTION_THRESHOLD;
    fixtureGusano.filter.categoryBits = CollisionCategories::WORM_COLL;
    fixtureGusano.filter.maskBits = (CollisionCategories::BOUNDARY_COLL | CollisionCategories::PROJECTILE_COLL);
    fixtureGusano.filter.maskBits &= ~CollisionCategories::WORM_COLL;
              
    this->body->SetFixedRotation(true); // Evita que rote

    this->body->CreateFixture(&fixtureGusano);
}

/*
 * Metodos de MOVIMIENTO del gusano.
 * */

void Worm::StartMovement(int dir) {
    if (this->isAirborne()) return;
    if(armaActual){
        return;
    }
    facingDirection = dir;
    moving = true;
}

void Worm::Move() {
    b2Vec2 velocity = body->GetLinearVelocity();
    float desiredVel = 0;
    float sp = 0;

    if(super_velocidad == false) {
        sp = MOVING_SPEED;
    } else {
        sp = SUPER_SPEED;
    }

    switch(facingDirection) {
        case RIGHT:
            desiredVel = sp;
            break;
        case LEFT:
            desiredVel = -1 * sp;
            break;
    }
    float velChange = desiredVel - velocity.x;
    status = WormStates::WALK;
    float impulse = body->GetMass() * velChange;
    body->ApplyLinearImpulse( b2Vec2 (impulse, 0), body->GetWorldCenter(), true);
}

void Worm::Stop() {
    moving = false;
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;
    body->SetLinearVelocity(velocity);
    status = WormStates::IDLE;
}

void Worm::JumpForward() {
    if (this->isAirborne()) return;
    if (this->isMoving()) Stop();
    status = WormStates::JUMP;
    jumping = true;

    float multiplier = 0;
    float velocity_ = 0;

    if(super_salto == false) {
        multiplier = FORWARD_JUMP_IMPULSE_MULTIPLIER;
        velocity_ = FORWARD_JUMP_X_VELOCITY;
    } else {
        multiplier = SUPER_FORWARD_JUMP_IMPULSE_MULTIPLIER;
        velocity_ = SUPER_FORWARD_JUMP_X_VELOCITY;
    }

    float impulse = body->GetMass() * multiplier;
    body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);

    b2Vec2 velocity = body->GetLinearVelocity();
    switch(facingDirection) {
        case RIGHT:
            velocity.x = velocity_;
            break;
        case LEFT:
            velocity.x = -1 * velocity_;
            break;
    }
    body->SetLinearVelocity(velocity);
}

void Worm::JumpBackward() {
    if (this->isAirborne()) return;
    if (this->isMoving()) Stop();
    status = WormStates::BACKFLIP;
    jumping = true;

    float multiplier = 0;
    float velocity_ = 0;

    if(super_salto == false) {
        multiplier = BACKWARD_JUMP_IMPULSE_MULTIPLIER;
        velocity_ = BACKWARD_JUMP_X_VELOCITY;
    } else {
        multiplier = SUPER_BACKWARD_JUMP_IMPULSE_MULTIPLIER;
        velocity_ = SUPER_BACKWARD_JUMP_X_VELOCITY;
    }

    float impulse = body->GetMass() * multiplier;
    body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);

    b2Vec2 velocity = body->GetLinearVelocity();
    switch(facingDirection) {
        case RIGHT:
            velocity.x = -1 * velocity_;
            break;
        case LEFT:
            velocity.x = velocity_;
            break;
    }
    body->SetLinearVelocity(velocity);
}

void Worm::cambiar_direccion(uint8_t dir){
    if(this->isDead()){
        return;
    }
    switch (dir)
    {
        case (RIGHT):
        {
            this->facingDirection = RIGHT;
            break;
        }
        case (LEFT):{
            this->facingDirection = LEFT;
            break;
        }
    }
}

/* Metodos que se llaman cuando determinados eventos ocurren */

void Worm::startGroundContact() {
    ++numBeamContacts;
    status = WormStates::IDLE;
    sounds.push(SoundTypes::GROUND_CONTACT);
    jumping = false;
    airborne = false;
    b2Vec2 position = body->GetPosition();
    finalHeight = position.y;
    float heightDiff = initialHeight - finalHeight;
    if (heightDiff < 2) return;
    if (2 < heightDiff && heightDiff < 25) {
        takeDamage((int)heightDiff);
    }
    else if (heightDiff >= 25){
        takeDamage(25);
    }
}

void Worm::endGroundContact() {
    --numBeamContacts;
    if (!jumping) {
        status = WormStates::FALL;
    }
    if (numBeamContacts == 0) {
        airborne = true;
        b2Vec2 position = body->GetPosition();
        initialHeight = position.y;
    }
}

void Worm::startWaterContact() {
    sounds.push(SoundTypes::SPLASH);
    this->hitPoints = 0;
}

void Worm::takeDamage(int damage) {
    sounds.push(SoundTypes::HURT_WORM);
    tomoDmgEsteTurno = true;
    hitPoints -= damage;
    if(hitPoints <= 0){
        hitPoints = 0;
    }
}

void Worm::heal(int hit_points) {
    hitPoints += hit_points;
    if (hitPoints > maxHealth)
        hitPoints = maxHealth;
}

void Worm::reload_weapons() {
    coleccionArmas->recargar_armas();
}

void Worm::kill() {
    sounds.push(SoundTypes::WORM_DEATH_CRY);
    dead_posiiton_x = body->GetPosition().x;
    dead_position_y = body->GetPosition().y;
    dead_position_angle = body->GetAngle();
    body->GetWorld()->DestroyBody(body);
    status = WormStates::DEAD;
    this->hitPoints = 0;
}

void Worm::detener_acciones(){
    if(!airborne){
        angulo_disparo = 0;
        apuntando = false;
        status = WormStates::IDLE;
        this->Stop();
        armaActual = nullptr;
        pudo_cambiar_de_arma = true;
    }
}

/*
 * Metodos para obtener informacion sobre el estado actual del gusano.
 * */

bool Worm::isMoving() {
    return moving;
}

bool Worm::isAirborne() {
    return airborne;
}

bool Worm::isDead() {
    return (this->hitPoints <= 0) ? true : false;
}

bool Worm::esta_apuntando(){
    return apuntando;
}

bool Worm::esta_cargando_arma() {
    if(!this->armaActual || this->isDead()){
        return false;
    }
    return this->armaActual->estaCargando();
}

bool Worm::esta_quieto() {
    if (status == WormStates::DEAD) return true;
    b2Vec2 velocity = body->GetLinearVelocity();
    return (velocity.x == 0 && velocity.y == 0);
}

bool Worm::tomo_dmg_este_turno() { return tomoDmgEsteTurno; }

/*
 * Metodos de combate de gusano.
 * */

void Worm::cambiar_arma(uint8_t id_arma){
    if (isAirborne() || this->isDead()) return;
    
    switch (id_arma)
    {
    case Armas::BAZOOKA:
        status = WormStates::BAZOOKA_AIMING;
        break;
    
    case Armas::MORTERO:
        status = WormStates::MORTAR_AIMING;
        break;
    
    case Armas::GRANADA_VERDE:
        status = WormStates::GREEN_GRENADE_AIMING;
        break;
    
    case Armas::DINAMITA:
        status = WormStates::DINAMITA_AIMING;
        break;
    
    case Armas::BATE:
        sounds.push(SoundTypes::BAT_EQUIP);
        status = WormStates::BATE_AIMING;
        break;
    
    case Armas::ATAQUE_AEREO:
        status = WormStates::AIR_ATTACK_AIMING;
        break;
    
    case Armas::GRANADA_SANTA:
        status = WormStates::HOLY_GRANADE_AIMING;
        break;
    
    case Armas::GRANADA_ROJA:
        status = WormStates::RED_GRENADE_AIMING;
        break;
    
    case Armas::BANANA:
        status = WormStates::BANANA_AIMING;
        break;
    
    case Armas::TELETRANSPORTACION:
        status = WormStates::TELEPORT_AIMING;
        break;
    
    default:
        break;
    }
    armaActual = coleccionArmas->SeleccionarArma(id_arma);
    if(armaActual->get_ammo() == 0){
        armaActual = nullptr;
        status = WormStates::IDLE;
        pudo_cambiar_de_arma = false;
    }
    else{
        pudo_cambiar_de_arma = true;
    }

}

void Worm::iniciar_carga() {
    if(!this->armaActual || this->isDead()){
        return;
    }
    this->armaActual->iniciarCarga();
}

void Worm::cargar_arma(){
    if(this->isDead()) return;
    if(!this->armaActual) return;
    this->armaActual->cargar();
}

bool Worm::usar_arma(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id) {
    if(!armaActual || this->isDead()) return false;
    Armas tipo = armaActual->obtenerTipo();
    if (tipo == TELETRANSPORTACION) {
        sounds.push(SoundTypes::TELEPORT);
        body->SetTransform(b2Vec2 (x_target, y_target), body->GetAngle());
        body->SetAwake(true);
        pudo_cambiar_de_arma = true;
        return true;
    }
    b2Vec2 position = body->GetPosition();
    float angle;
    if (tipo == ATAQUE_AEREO) {
        status = WormStates::AIR_ATTACK_SHOOTING;
        sounds.push(SoundTypes::AIR_STRIKE);
        position = b2Vec2 (x_target, y_target);
        angle = 1.5f * b2_pi;
    }
    else {
        if (tipo == DINAMITA) {
            if (this->facingDirection == RIGHT) {
                angle = 0;
            }
            else {
                angle = b2_pi;
            }
        }
        else {
            if (tipo == BAZOOKA || tipo == MORTERO) {
                sounds.push(SoundTypes::WORM_BAZOOKA_SHOUT);
            }
            if (tipo == BATE) {
                status = WormStates::BATE_SHOOTING;
                sounds.push(SoundTypes::BAT_ATTACK);
            }
            else {
                sounds.push(SoundTypes::WORM_GRENADE_SHOUT);
            }
            if(this->facingDirection == LEFT){
                if(this->get_aiming_angle() < 0){
                    angle =  (- this->get_aiming_angle()) + 3.14;
                }
                else{
                    angle = 3.14f - this->get_aiming_angle();
                    
                }
            }
            else{
                angle = this->get_aiming_angle();
            }
        }
    }
    
    apuntando = false;
    armaActual->Shoot(projectiles, entity_id, position.x, position.y, angle);
    status = WormStates::IDLE;
    armaActual = nullptr;
    pudo_cambiar_de_arma = true;
    return true;
}

void Worm::esta_apuntando_para(bool id){
    apuntando = true;
    this->esta_apuntando_para_arriba = id;
}

void Worm::resetear_dmg() {
    tomoDmgEsteTurno = false;
}

void Worm::incrementar_angulo_en(float inc){
    if(!esta_apuntando_para_arriba){
        inc = -inc;
    }
    if(angulo_disparo + inc < -1.57){
        angulo_disparo = -1.57f;
        return;
    }
    else if (angulo_disparo + inc > 1.57){
        angulo_disparo = 1.57f;
        return;
    }
    angulo_disparo +=inc;
}

void Worm::set_target(float x, float y) {
    this->x_target = x;
    this->y_target = y;
}

void Worm::set_grenade_timer(int seconds) {
    std::shared_ptr<GranadaArma> arma = std::dynamic_pointer_cast<GranadaArma>(armaActual);
    if (!arma) return;
    arma->SetTime(seconds);
}

void Worm::parar_angulo(){
    apuntando = false;
}

void Worm::aumentar_vida(int vida){
    hitPoints+= vida;
    maxHealth+=vida;
}

/*
 * Funciones GETTER para comunicar informacion del gusano.
 * */

std::vector<float> Worm::GetPosition() {
    if(status == WormStates::DEAD){
        return std::vector<float>({dead_posiiton_x,dead_position_y});
    }
    b2Vec2 position = body->GetPosition();
    return std::vector<float> ({position.x, position.y});
}

int Worm::get_facing_direction(){
    return this->facingDirection;
}

uint8_t Worm::get_status(){
    return this->status;
}

uint32_t Worm::get_id(){
    return this->id;
}

float Worm::get_angulo(){
    if(status == WormStates::DEAD){
        return dead_position_angle;
    }
    return this->body->GetAngle();
}

float Worm::get_aiming_angle(){
    return angulo_disparo;
}

uint8_t Worm::get_vida() {
    return hitPoints;
}

bool Worm::using_teleportacion(){
    if(!this->armaActual){
        return false;
    }
    return (this->armaActual->obtenerTipo() == Armas::TELETRANSPORTACION);
}

bool Worm::using_ataque_aereo(){
    if(!this->armaActual){
        return false;
    }
    return (this->armaActual->obtenerTipo() == Armas::ATAQUE_AEREO);
}

std::vector<float> Worm::posicion_marcada(){
    if(!this->armaActual){
        return std::vector<float>({0,0});
    }
    else{
        return std::vector<float>({x_target,y_target});
    }
}

bool Worm::using_timer(){
    if(!this->armaActual)return false;
    Armas tipo = this->armaActual->obtenerTipo();
    bool esta_usando_timer = false;
    switch(tipo){
        case(Armas::DINAMITA):{
            esta_usando_timer = true;
            break;
        }
        case(Armas::GRANADA_ROJA):{
            esta_usando_timer = true;
            break;
        }
        case(Armas::BANANA):{
            esta_usando_timer = true;
            break;
        }
        case(Armas::GRANADA_SANTA):{
            esta_usando_timer = true;
            break;
        }
        case(Armas::GRANADA_VERDE):{
            esta_usando_timer = true;
            break;
        }
        default:{
            esta_usando_timer = false;
            break;
        }
    }
    return esta_usando_timer;
}

float Worm::get_timer(){
    if(!armaActual){
        return 0;
    }
    std::shared_ptr<GranadaArma> granada = std::dynamic_pointer_cast<GranadaArma>(this->armaActual);
    return granada->get_timer();
}

std::vector<std::pair<int,int>> Worm::get_municiones(){
    return this->coleccionArmas->obtener_municion_armas();
}

uint16_t Worm::get_carga_actual(){
    if(!armaActual) return 0;
    if(armaActual->obtenerTipo()== Armas::TELETRANSPORTACION) return 0;
    return armaActual->get_carga();
}

void Worm::reducir_vida() {
    if(this->status != WormStates::DEAD) {
        this->hitPoints = 1;
    }
}

void Worm::super_velocidad_gusano() {
    super_velocidad = !super_velocidad;
}

void Worm::super_salto_gusano() {
    super_salto = !super_salto;
}

bool Worm::get_pudo_cambiar_de_arma(){
    bool bis = this->pudo_cambiar_de_arma;
    this->pudo_cambiar_de_arma = true;
    return bis;
}
