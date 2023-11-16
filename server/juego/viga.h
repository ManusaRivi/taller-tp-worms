#ifndef VIGA_H
#define VIGA_H

#include "../../libs/box2d/include/box2d/box2d.h"

enum beamSize {
    SMALL,
    LARGE,
};

#define SMALL_LENGTH 1.5f
#define LARGE_LENGTH 100.0f

#define HEIGHT 0.40f

#define BEAM_DENSITY 0.0f

class Viga {
private:
    b2Body* body;
public:
    Viga(b2World& world, beamSize type, float x_pos, float y_pos, float angle, uint16 collisionCategory, uint16 collisionMask);
};

#endif
