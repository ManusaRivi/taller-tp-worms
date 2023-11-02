#include "worm.h"

Worm::Worm(b2Body* body, int direction) : body(body), facingDirection(direction), jumpSteps(0) {}

void Worm::Move(int dir) {
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
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;
    body->SetLinearVelocity(velocity);
}

void Worm::JumpForward() {
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

b2Vec2 Worm::GetPosition() {
    return body->GetPosition();
}
