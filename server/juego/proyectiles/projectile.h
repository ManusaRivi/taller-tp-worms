#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../../common/projectile_types.h"
#include "../collision_categories.h"
#include "../colisionable.h"

class Projectile : public Colisionable 
{
protected:
    b2Body* body;
    ProjectileType type;
    bool exploded = false;
    int fragments;
    void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower)
    {
        b2Vec2 blastDir = applyPoint - blastCenter;
        float distance = blastDir.Normalize();
        if (distance == 0)
            return;

        float inverseDistance = 1 / distance;
        float impulseMagnitude = blastPower * inverseDistance * inverseDistance;
        body->ApplyLinearImpulse(impulseMagnitude * blastDir, applyPoint, true);
    }

public:
    Projectile() {};
    virtual bodyType identificar() override {
        return bodyType::PROJECTILE;
    }
    virtual ProjectileType getType() = 0;
    virtual bool hasExploded() {
        return exploded;
    }
    virtual int getFragCount() {
        return fragments;
    }
    virtual b2Vec2 getPosition() {
        return body->GetPosition();
    }
    virtual float getAngle() {
        return body->GetAngle();
    }
    virtual void updateAngle() {
        b2Vec2 velocity = body->GetLinearVelocity();
        float newAngle = atan2(velocity.x, velocity.y);
        body->SetTransform(body->GetPosition(), newAngle);
    }
    virtual void explotar() = 0;
    virtual ~Projectile() {}
};

#endif
