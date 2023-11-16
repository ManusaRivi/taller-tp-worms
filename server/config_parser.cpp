#include "config_parser.h"

void ConfigParser::parse_config() {
    std::map<Config, int> config;
    YAML::Node config_data = YAML::LoadFile(CONFIG_PATH);
    config[Config::HIT_POINTS] = config_data["puntos_de_vida"].as<int>();
    config[Config::BAZOOKA_DMG] = config_data["dmg_bazooka"].as<int>();
    config[Config::BAZOOKA_RADIUS] = config_data["radio_bazooka"].as<int>();
}

ConfigParser::ConfigParser() {
    parse_config();
}
