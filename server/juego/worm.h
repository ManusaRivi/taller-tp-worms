#ifndef WORM_H
#define WORM_H

#include "../../libs/box2d/include/box2d/box2d.h"

#define RIGHT 0
#define LEFT 1

#define MOVING_SPEED 1

#define FORWARD_JUMP_STEPS 38
#define BACKWARD_JUMP_STEPS 58

#define FORWARD_JUMP_IMPULSE_MULTIPLIER 3.25
#define BACKWARD_JUMP_IMPULSE_MULTIPLIER 5

#define FORWARD_JUMP_X_VELOCITY 1.62
#define BACKWARD_JUMP_X_VELOCITY 0.2

class Worm {
private:
    b2Body* body;
    int facingDirection;
public:
    int jumpSteps;
    Worm(b2Body* body, int direction);
    void Move(int dir);
    void Stop();
    void JumpForward();
    void JumpBackward();

    b2Vec2 GetPosition();
};

#endif
