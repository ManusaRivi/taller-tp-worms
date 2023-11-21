#ifndef WORM_QUERY_H
#define WORM_QUERY_H

#include <vector>

#include "../../box2d/include/box2d/box2d.h"
#include "./worm.h"
#include "./colisionable.h"

class WormQuery : public b2QueryCallback
{
public:
    std::vector<b2Body*> foundBodies;

    bool ReportFixture(b2Fixture* fixture) 
    {
        b2Body* body = fixture->GetBody();
        Colisionable* colisionable = (Colisionable*) body->GetUserData().pointer;
        if (colisionable->identificar() == bodyType::WORM) {
            foundBodies.push_back(fixture->GetBody());
        }
        return true;
    }
};

#endif
