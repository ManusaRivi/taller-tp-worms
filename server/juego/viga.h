#ifndef VIGA_H
#define VIGA_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "./collision_categories.h"

enum beamSize {
    SMALL,
    LARGE,
};

#define SMALL_LENGTH 1.5f
#define LARGE_LENGTH 3.0f

#define HEIGHT 0.40f

#define BEAM_DENSITY 0.0f
#define BEAM_FRICTION 0.8f

class Viga {
private:
    b2Body* body;
public:
    Viga(b2World& world, int type, float x_pos, float y_pos, float angle);
};

#endif
