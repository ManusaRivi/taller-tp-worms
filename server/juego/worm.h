#ifndef WORM_H
#define WORM_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "./collision_categories.h"

#include <vector>

enum directions {
    RIGHT = 0,
    LEFT = 1,
};

#define BOX_WIDTH 0.5f
#define BOX_HEIGHT 0.5f

#define WORM_DENSITY 0.2f
#define WORM_FRICTION 1.0f

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
    bool airborne;
    int hitPoints;
    float initialHeight;
    float finalHeight;
    uint32_t id;
public:
    int jumpSteps;
    Worm(b2World& world, int direction, float x_pos, float y_pos, int hitPoints);
    void Move(int dir);
    void Stop();
    void JumpForward();
    void JumpBackward();
    void startGroundContact();
    void endGroundContact();
    bool isAirborne();
    void takeDamage(int damage);
    std::vector<float> GetPosition();
    float GetAngle();

    int get_facing_direction();

    uint32_t get_id();
};

#endif
