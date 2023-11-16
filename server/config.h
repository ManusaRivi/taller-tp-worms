#ifndef CONFIG_H
#define CONFIG_H

#include <map>

enum Config {
    HIT_POINTS,
    BAZOOKA_DMG,
    BAZOOKA_RADIUS
};

extern std::map<Config, int> config;

#endif
