#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../../../box2d/include/box2d/box2d.h"
#include "../colisionable.h"

class Projectile : public Colisionable 
{
protected:
    b2Body* body;
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
    virtual b2Vec2 getPosition() {
        return body->GetPosition();
    }
    virtual float getAngle() {
        return body->GetAngle();
    }
    virtual void lanzar(float angle, float power) = 0;
    virtual void explotar() = 0;
    virtual ~Projectile() {}
};

#endif
