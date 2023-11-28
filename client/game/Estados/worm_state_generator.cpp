#include "worm_state_generator.h"

std::unique_ptr<WormState> WormStateGenerator::get_state_with_code(int status_code,
                                                            bool facing_right,
                                                            float worm_angle,
                                                            float shot_angle) {
    unsigned int frames = 0;
    switch (status_code)
    {
    case WormStates::IDLE:
        return std::make_unique<WIdle>(facing_right, worm_angle);
    
    case WormStates::WALK:
        return std::make_unique<WWalk>(facing_right, worm_angle);
    
    case WormStates::BAZOOKA_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimBaz"), frames, facing_right, worm_angle, shot_angle);

    case WormStates::HOLY_GRANADE_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimHGr"), frames, facing_right, worm_angle, shot_angle);

    case WormStates::GREEN_GRENADE_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimGr"), frames, facing_right, worm_angle, shot_angle);

    case WormStates::BANANA_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimBan"), frames, facing_right, worm_angle, shot_angle);

    case WormStates::RED_GRENADE_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimRGr"), frames, facing_right, worm_angle, shot_angle);

    case WormStates::DEAD:
        return std::make_unique<Grave>(facing_right, worm_angle);
    
    case WormStates::JUMP:
        return std::make_unique<WJump>(facing_right, worm_angle);
    
    case WormStates::BACKFLIP:
        return std::make_unique<WBackflip>(facing_right, worm_angle);
    
    case WormStates::FALL:
        return std::make_unique<WFall>(facing_right, worm_angle);
    
    case WormStates::BATE_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimBate"), frames, facing_right, worm_angle, shot_angle);
    
    case WormStates::BATE_SHOOTING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WShootBate"), frames, facing_right, worm_angle, shot_angle);
    
    case WormStates::TELEPORT_AIMING:
        return std::make_unique<WTeleportAiming>(facing_right, worm_angle);
    
    case WormStates::TELEPORT_SHOOTING:
        return std::make_unique<WTeleportShooting>(facing_right, worm_angle);
    
    case WormStates::DINAMITA_AIMING:
        return std::make_unique<WDynAiming>(facing_right, worm_angle);
    
    case WormStates::AIR_ATTACK_AIMING:
        return std::make_unique<WAirAiming>(facing_right, worm_angle);
    
    case WormStates::MORTAR_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimBaz"), frames, facing_right, worm_angle, shot_angle);

    case WormStates::AIR_ATTACK_SHOOTING:
        return std::make_unique<WAirShooting>(facing_right, worm_angle);
    
    case WormStates::WINNER:
        return std::make_unique<WWinner>(facing_right, worm_angle);

    default:
        throw std::runtime_error("WormStateGenerator: No existe ese codigo de estado");
    }
                                                            }