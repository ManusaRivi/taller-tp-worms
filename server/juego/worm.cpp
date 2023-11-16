#include "worm.h"

Worm::Worm(b2World& world, int hitPoints, int direction, float x_pos, float y_pos, uint16 collisionCategory, uint16 collisionMask) : 
            facingDirection(direction), airborne(false), hitPoints(hitPoints), initialHeight(0.0f), finalHeight(0.0f), jumpSteps(0)
{
    b2BodyDef gusanoDef;
    gusanoDef.type = b2_dynamicBody;
    gusanoDef.position.Set(x_pos, y_pos);
    b2Body *gusano = world.CreateBody(&gusanoDef);
    this->body = gusano;

    b2PolygonShape gusanoBox;
    gusanoBox.SetAsBox(BOX_WIDTH, BOX_HEIGHT);

    b2FixtureDef fixtureGusano;
    fixtureGusano.shape = &gusanoBox;
    fixtureGusano.density = WORM_DENSITY;
    fixtureGusano.friction = WORM_FRICTION;
    fixtureGusano.filter.categoryBits = collisionCategory;
    fixtureGusano.filter.maskBits = collisionMask;

    this->body->CreateFixture(&fixtureGusano);
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

b2Vec2 Worm::GetPosition() {
    return body->GetPosition();
}

int Worm::get_facing_direction(){
    return this->facingDirection;
}

uint32_t Worm::get_id(){
    return this->id;
}