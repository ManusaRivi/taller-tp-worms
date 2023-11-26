#include "contact_listener.h"

CollisionType ContactListener::getCollisionType(Colisionable* bodyA, Colisionable* bodyB) {
    bodyType tipoA = bodyA->identificar();
    bodyType tipoB = bodyB->identificar();
    if (tipoA == bodyType::WORM && tipoB == bodyType::BEAM) return CollisionType::WORM_VIGA;
    if (tipoA == bodyType::BEAM && tipoB == bodyType::WORM) return CollisionType::VIGA_WORM;
    if (tipoA == bodyType::PROJECTILE && tipoB == bodyType::WORM) return CollisionType::PROYECTIL_WORM;
    if (tipoA == bodyType::WORM && tipoB == bodyType::PROJECTILE) return CollisionType::WORM_PROYECTIL;
    if (tipoA == bodyType::PROJECTILE && tipoB == bodyType::BEAM) return CollisionType::PROYECTIL_VIGA;
    if (tipoA == bodyType::WATER && tipoB == bodyType::WORM) return CollisionType::WORM_WATER;
    if (tipoA == bodyType::WORM && tipoB == bodyType::WATER) return CollisionType::WATER_WORM;
    return CollisionType::VIGA_PROYECTIL;
}

void ContactListener::BeginContact(b2Contact* contact) {
    Colisionable* bodyA = (Colisionable*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Colisionable* bodyB = (Colisionable*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    CollisionType type = getCollisionType(bodyA, bodyB);
    switch (type) {
        case WORM_VIGA:
        {
            Worm* worm = static_cast<Worm*>(bodyA);
            worm->startGroundContact();
        }
        break;
        case VIGA_WORM:
        {
            Worm* worm = static_cast<Worm*>(bodyB);
            worm->startGroundContact();
        }
        break;
        case PROYECTIL_WORM:
        {
            Projectile* projectile = static_cast<Projectile*>(bodyA);
            // if (projectile->getType() != ProjectileType::GRENADE)
            if (!projectile->isGrenade()){
                projectile->SetExplosion();
            }
            else {
                Grenade* grenade = static_cast<Grenade*>(projectile);
                grenade->bounce();
            }
        }
            break;
        case WORM_PROYECTIL:
        {
            Projectile* projectile = static_cast<Projectile*>(bodyB);
            if (!projectile->isGrenade()) {
                projectile->SetExplosion();
            }
            else {
                Grenade* grenade = static_cast<Grenade*>(projectile);
                grenade->bounce();
            }
        }
            break;
        case PROYECTIL_VIGA:
        {
            Projectile* projectile = static_cast<Projectile*>(bodyA);
            if (!projectile->isGrenade()) {
                projectile->SetExplosion();
            }
            else {
                Grenade* grenade = static_cast<Grenade*>(projectile);
                grenade->bounce();
            }
        }
            break;
        case VIGA_PROYECTIL:
        {
            Projectile* projectile = static_cast<Projectile*>(bodyB);
            if (!projectile->isGrenade()) {
                projectile->SetExplosion();
            }
            else {
                Grenade* grenade = static_cast<Grenade*>(projectile);
                grenade->bounce();
            }
        }
        case WATER_WORM:
        {
            Worm* worm = static_cast<Worm*>(bodyA);
            worm->startWaterContact();
        }
        case WORM_WATER:
        {
            Worm* worm = static_cast<Worm*>(bodyB);
            worm->startWaterContact();
        }
            break;
    }
}

void ContactListener::EndContact(b2Contact* contact) {
    Colisionable* bodyA = (Colisionable*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Colisionable* bodyB = (Colisionable*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    CollisionType type = getCollisionType(bodyA, bodyB);

    switch (type) {
        case WORM_VIGA:
        {
            Worm* worm = static_cast<Worm*>(bodyA);
            worm->endGroundContact();
        }
        break;
        case VIGA_WORM:
        {
            Worm* worm = static_cast<Worm*>(bodyB);
            worm->endGroundContact();
        }
        break;
        case PROYECTIL_WORM: break;
        case WORM_PROYECTIL: break;
        case PROYECTIL_VIGA: break;
        case VIGA_PROYECTIL: break;
        case WATER_WORM: break;
        case WORM_WATER: break;
    }
}
