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
    b2Body* body;
    ProjectileType type;
    bool exploded = false;
    int fragments;
    int dmg;
    int radius;
    uint32_t id;
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
    Projectile() {};
    virtual bodyType identificar() override {
        return bodyType::PROJECTILE;
    }
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
    virtual void explotar() = 0;
    virtual ~Projectile() {
        body->GetWorld()->DestroyBody(body);
    }
    virtual uint32_t get_id(){
        return this->id;
    }

    virtual void insertar_id(uint32_t id_recibido){
        this->id = id_recibido;
    }
};

#endif
