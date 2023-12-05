#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <queue>

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../../common/projectile_types.h"
#include "../../../../common/sound_types.h"
#include "../collision_categories.h"
#include "../colisionable.h"

class Projectile : public Colisionable 
{
protected:
    b2World& world;
    b2Body* body;
    ProjectileType type;
    uint32_t id;
    int dmg;
    int radius;
    int fragments;
    bool exploded = false;
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
    std::queue<SoundTypes> sounds;
    Projectile(b2World& world, ProjectileType type, uint32_t id, float x_pos, float y_pos, int dmg, int radius, int fragments) :
                Colisionable(bodyType::PROJECTILE),world(world), type(type), id(id), dmg(dmg), radius(radius), fragments(fragments) {};

    ProjectileType getType() {
        return type;
    }
    virtual bool isGrenade() = 0;
    bool hasExploded() {
        return exploded;
    }
    int getFragCount() {
        return fragments;
    }
    b2Vec2 getPosition() {
        return body->GetPosition();
    }
    float getRadius() {
        return radius;
    }
    float getAngle() {
        return body->GetAngle();
    }
    void updateAngle() {
        b2Vec2 velocity = body->GetLinearVelocity();
        float newAngle = atan2(velocity.x, velocity.y);
        body->SetTransform(body->GetPosition(), newAngle);
    }
    void SetExplosion() {
        exploded = true;
        sounds.push(SoundTypes::EXPLOSION);
    }
    virtual void pushByWind(float wind_force) {}
    virtual void explotar() = 0;
    uint32_t get_id(){
        return this->id;
    }
    virtual ~Projectile() {
        body->GetWorld()->DestroyBody(body);
    }
};

#endif
