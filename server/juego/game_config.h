#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <yaml-cpp/yaml.h>

class GameConfig
{
private:
    YAML::Node config;
    GameConfig() :  config(YAML::LoadFile("../configuration.yaml")),
                    puntos_de_vida(config["puntos_de_vida"].as<int>()),
                    bazooka_dmg(config["dmg_bazooka"].as<int>()),
                    bazooka_radius(config["cantidad_de_vidas"].as<int>()) {}
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;
public:
    const int puntos_de_vida;
    const int bazooka_dmg;
    const int bazooka_radius;

    static GameConfig& getInstance()
    {
        static GameConfig instance;
        return instance;
    }
};

#endif
