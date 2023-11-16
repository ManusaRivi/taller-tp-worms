#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <yaml-cpp/yaml.h>
#include "./config.h"

#define CONFIG_PATH "../game_config.yaml"

class ConfigParser
{
private:
    void parse_config();
public:
    ConfigParser();
};

#endif
