//
// Created by Alexander Stiles on 15/09/22.
//

#ifndef SOFTWARE_CONFIG_H
#define SOFTWARE_CONFIG_H

#include "mosfet.h"

#define MAX_CONFIGS 8
#define MAX_NAME_CHARS 15

typedef struct {
    uint8_t id; // ID of config
    char config_name[MAX_NAME_CHARS]; // Name of config
    bool selected; // Whether this config is selected
    mosfet_group_t mosfet_group; // Mosfet group to modify to select / deselect config
} config_t;

typedef struct {
    config_t* selected_config; // Currently selected config
    config_t configs[MAX_CONFIGS]; // All the available config
    uint8_t num_configs;
} config_manager_t;

config_t create_config(const char config_name[], mosfet_group_t mosfet_group);

config_manager_t create_config_manager();
bool add_config(config_manager_t* config_manager, config_t config);
bool select_config_by_ID(config_manager_t* config_manager, uint8_t id);

#endif //SOFTWARE_CONFIG_H
