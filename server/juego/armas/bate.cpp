#include "bate.h"

Bate::Bate(b2World& world, int dmg) : world(world), dmg(dmg) { tipo = Armas::BATE; }

void Bate::iniciarCarga() {}

void Bate::cargar() {}

bool Bate::estaCargando() { return false; }

void Bate::Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) {
    WormQuery wormQuery;
    b2AABB aabb;
    float hitbox_offset = HITBOX_OFFSET;
    if (abs(angle) > (b2_pi / 2)) {
        hitbox_offset *= -1;
    }
    b2Vec2 center (x_pos + hitbox_offset, y_pos);
    aabb.lowerBound = center - b2Vec2(HITBOX_HALF_SIDE, HITBOX_HALF_SIDE);
    aabb.upperBound = center + b2Vec2(HITBOX_HALF_SIDE, HITBOX_HALF_SIDE);

    world.QueryAABB(&wormQuery, aabb);

    for (size_t i = 0; i < wormQuery.foundBodies.size(); ++i) {
        b2Body* wormBody = wormQuery.foundBodies[i];

        b2Vec2 impulseVec (IMPULSE * cos(angle), IMPULSE * sin(angle));
        wormBody->ApplyLinearImpulse(impulseVec, wormBody->GetWorldCenter(), true);

        Worm* worm = (Worm*) wormBody->GetUserData().pointer;
        worm->takeDamage(dmg);
    }
}

int Bate::get_ammo(){
    return 999;
}
int Bate::get_carga() {
    return 0;
}
