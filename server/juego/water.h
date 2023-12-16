#ifndef WATER_H
#define WATER_H

#define LENGTH 780
#define HEIGHT 0.40f

#include "../../libs/box2d/include/box2d/box2d.h"
#include "./collision_categories.h"
#include "./colisionable.h"

class Water: public Colisionable {
private:
    b2Body* body;
public:
    Water(b2World& world);
    ~Water();
};

#endif
