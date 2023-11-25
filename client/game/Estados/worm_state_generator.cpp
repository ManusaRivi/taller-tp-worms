#include "worm_state_generator.h"

std::unique_ptr<WormState> WormStateGenerator::get_state_with_code(int status_code,
                                                            bool facing_right,
                                                            float worm_angle,
                                                            float shot_angle) {
    unsigned int frames = 0;
    switch (status_code)
    {
    case WORM_STATE_IDLE:
        return std::make_unique<WIdle>(facing_right, worm_angle);
    
    case WORM_STATE_WALKING:
        return std::make_unique<WWalk>(facing_right, worm_angle);
    
    case WORM_STATE_BAZOOKA_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimBaz"), frames, facing_right, worm_angle, shot_angle);

    case WORM_STATE_HOLY_GRANADE_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimHGr"), frames, facing_right, worm_angle, shot_angle);

    case WORM_STATE_GRANADE_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimGr"), frames, facing_right, worm_angle, shot_angle);

    case WORM_STATE_BANANA_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimBan"), frames, facing_right, worm_angle, shot_angle);

    case WORM_STATE_RED_GRANADE_AIMING:
        frames = 31;
        return std::make_unique<WAiming>(std::string("WAimRGr"), frames, facing_right, worm_angle, shot_angle);

    case WORM_STATE_DEAD:
        return std::make_unique<Grave>(facing_right, worm_angle);
        
    default:
        throw std::runtime_error("WormStateGenerator: No existe ese codigo de estado");
    }
                                                            }