#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <yaml-cpp/yaml.h>

class GameConfig
{
private:
    YAML::Node config;
    GameConfig() :  config(YAML::LoadFile(PROJECT_SOURCE_DIR "/game_config.yaml")),
                    puntos_de_vida(config["puntos_de_vida"].as<int>()),
                    frag_amount(config["cantidad_frags"].as<int>()),
                    frag_dmg(config["danio_frags"].as<int>()),
                    frag_radius(config["radio_frags"].as<int>()),
                    bazooka_dmg(config["dmg_bazooka"].as<int>()),
                    bazooka_radius(config["cantidad_de_vidas"].as<int>()),
                    mortar_dmg(config["dmg_mortero"].as<int>()),
                    mortar_radius(config["radio_mortero"].as<int>()) {}
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;
public:
    const int puntos_de_vida;

    const int frag_amount;
    const int frag_dmg;
    const int frag_radius;

    const int bazooka_dmg;
    const int bazooka_radius;

    const int mortar_dmg;
    const int mortar_radius;

    static GameConfig& getInstance()
    {
        static GameConfig instance;
        return instance;
    }
};

#endif
