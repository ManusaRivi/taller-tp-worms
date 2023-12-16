#ifndef VIGA_H
#define VIGA_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "./collision_categories.h"
#include "./colisionable.h"
#include <vector>
#include <stdio.h>

enum beamSize {
    SMALL,
    LARGE,
};

#define SMALL_LENGTH 1.5f
#define LARGE_LENGTH 3.0f

#define HEIGHT 0.40f

#define BEAM_DENSITY 0.0f
#define BEAM_FRICTION 0.8f
#define BEAM_RESTITUTION_THRESHOLD 5.0f

class BeamServer : public Colisionable {
private:
    b2Body* body;
    float len;
public:
    BeamServer(b2World& world, int type, float x_pos, float y_pos, float angle);
    std::vector<float> get_pos();
};
    

#endif
