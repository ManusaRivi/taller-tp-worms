#include "worm.h"

Worm::Worm(b2World& world, int hitPoints, int direction, float x_pos, float y_pos, uint32_t id_) : 
            facingDirection(direction), airborne(false), hitPoints(hitPoints), initialHeight(0.0f),
            finalHeight(0.0f), jumpSteps(0), id(id_),status(0), angulo_disparo(0)
{
    b2BodyDef gusanoDef;
    gusanoDef.type = b2_dynamicBody;
    printf("La posicion en el constructo es %f  %f\n",x_pos,y_pos);
    gusanoDef.position.Set(x_pos, y_pos);
    b2Body *gusano = world.CreateBody(&gusanoDef);
    this->body = gusano;

    b2PolygonShape gusanoBox;
    gusanoBox.SetAsBox(BOX_WIDTH, BOX_HEIGHT);

    b2FixtureDef fixtureGusano;
    fixtureGusano.shape = &gusanoBox;
    fixtureGusano.density = WORM_DENSITY;
    fixtureGusano.friction = WORM_FRICTION;
    fixtureGusano.filter.categoryBits = CollisionCategories::WORM;
    fixtureGusano.filter.maskBits = (CollisionCategories::BOUNDARY | CollisionCategories::PROJECTILE);

    this->body->CreateFixture(&fixtureGusano);
    printf("luego de crearle las fixtures la posicion del gusano es %f   %f\n", body->GetPosition().x, body->GetPosition().y);
}

void Worm::Move(int dir) {
    if (jumpSteps > 0) return;
    b2Vec2 velocity = body->GetLinearVelocity();
    switch(dir) {
        case RIGHT:
            facingDirection = RIGHT;
            velocity.x = MOVING_SPEED;
            break;
        case LEFT:
            facingDirection = LEFT;
            velocity.x = -1 * MOVING_SPEED;
            break;
    }
    status = 1;
    body->SetLinearVelocity(velocity);
}

void Worm::Stop() {
    if (jumpSteps > 0) return;
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;
    body->SetLinearVelocity(velocity);
}

void Worm::JumpForward() {
    if (jumpSteps > 0) return;
    jumpSteps = FORWARD_JUMP_STEPS;
    float impulse = body->GetMass() * FORWARD_JUMP_IMPULSE_MULTIPLIER;
    body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);

    b2Vec2 velocity = body->GetLinearVelocity();
    switch(facingDirection) {
        case RIGHT:
            velocity.x = FORWARD_JUMP_X_VELOCITY;
            break;
        case LEFT:
            velocity.x = -1 * FORWARD_JUMP_X_VELOCITY;
            break;
    }
    body->SetLinearVelocity(velocity);
}

void Worm::JumpBackward() {
    if (jumpSteps > 0) return;
    jumpSteps = BACKWARD_JUMP_STEPS;
    float impulse = body->GetMass() * BACKWARD_JUMP_IMPULSE_MULTIPLIER;
    body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);

    b2Vec2 velocity = body->GetLinearVelocity();
    switch(facingDirection) {
        case RIGHT:
            velocity.x = -1 * BACKWARD_JUMP_X_VELOCITY;
            break;
        case LEFT:
            velocity.x = BACKWARD_JUMP_X_VELOCITY;
            break;
    }
    body->SetLinearVelocity(velocity);
}

void Worm::startGroundContact() {
    airborne = false;
    b2Vec2 position = body->GetPosition();
    finalHeight = position.y;
    float heightDiff = initialHeight - finalHeight;
    if (2 < heightDiff && heightDiff < 25) {
        takeDamage((int)heightDiff);
    }
    else if (heightDiff >= 25)
        takeDamage(25);
}

void Worm::endGroundContact() {
    airborne = true;
    b2Vec2 position = body->GetPosition();
    initialHeight = position.y;
}

bool Worm::isAirborne() {
    return airborne;
}

void Worm::takeDamage(int damage) {
    hitPoints -= damage;
}

std::vector<float> Worm::GetPosition() {
    b2Vec2 position = body->GetPosition();
    printf("Al pedire la posicion se devuelve %f   %f\n",position.x,position.y);
    return std::vector<float> ({position.x, position.y});
}

float Worm::GetAngle() {
    return body->GetAngle();
}

int Worm::get_facing_direction(){
    return this->facingDirection;
}

uint32_t Worm::get_id(){
    return this->id;
}

float Worm::get_angulo(){
    return this->body->GetAngle();
}

uint8_t Worm::get_status(){
    return this->status;
}

void Worm::cambiar_arma(uint8_t id_arma){
    if (isAirborne()){
        return;
    }
    status = id_arma;
}

void Worm::esta_apuntando_para(bool id){
    apuntando = true;
    this->esta_apuntando_para_arriba= id;
}

bool Worm::esta_apuntando(){
    return apuntando;
}

void Worm::incrementar_angulo_en(float inc){
    if(!esta_apuntando_para_arriba){
        inc = -inc;
        if(angulo_disparo + inc < 0){
            return;
        }
    }
    angulo_disparo +=inc;
}

void Worm::detener_acciones(){
    if(!airborne){
        angulo_disparo = 0;
        apuntando = false;
        status = 0;
        this->Stop();
    }
}

float Worm::aiming_angle(){
    return angulo_disparo;
}

void Worm::parar_angulo(){
    apuntando = false;
}