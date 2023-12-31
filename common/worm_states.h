#ifndef WORM_STATES_H
#define WORM_STATES_H

enum WormStates {
    // Movimiento
    IDLE,
    WALK,
    JUMP,
    BACKFLIP,
    FALL,
    DEAD,
    // Con armas
    BAZOOKA_AIMING,
    BATE_AIMING,
    BATE_SHOOTING,
    TELEPORT_AIMING,
    TELEPORT_SHOOTING,
    DINAMITA_AIMING,
    AIR_ATTACK_AIMING,
    AIR_ATTACK_SHOOTING,
    HOLY_GRANADE_AIMING,
    GREEN_GRENADE_AIMING,
    BANANA_AIMING,
    RED_GRENADE_AIMING,
    MORTAR_AIMING,
    WINNER
};

#endif