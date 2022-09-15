//
// Created by Alexander Stiles on 15/09/22.
//

#include "config.h"

#include <string.h>

static uint8_t config_id = 0;

/* CONFIG */

config_t create_config(const char config_name[], mosfet_group_t mosfet_group) {
    config_t config = {
            .id = config_id++,
            .selected = false,
            .mosfet_group = mosfet_group,
    };

    // Copy the name of the config
    memcpy(config.config_name, config_name, MAX_NAME_CHARS);

    return config;
}

/* CONFIG MANAGER */

config_manager_t create_config_manager() {
    config_manager_t config_manager = {
            .selected_config = NULL,
            .num_configs = 0,
    };

    return config_manager;
}

bool add_config(config_manager_t* config_manager, config_t config) {
    bool config_added = false;

    if (config_manager->num_configs + 1 < MAX_CONFIGS) {
        // Add new config and increment number of configs
        config_manager->configs[config_manager->num_configs++] = config;

        // Update flag
        config_added = true;
    }

    return config_added;
}

bool select_config_by_ID(config_manager_t* config_manager, uint8_t id) {
    bool config_selected = false;

    for (int i = 0; i < config_manager->num_configs; i++) {
        config_t* config = &config_manager->configs[i];

        if (config->id == id) {

            if (config_manager->selected_config != NULL) {
                // Deselect current config
                config_manager->selected_config->selected = false;

                // Disable MOSFET group of previous config
                disable_mosfet_group(&config_manager->selected_config->mosfet_group);
            }

            // Set the config to selected
            config->selected = true;
            config_manager->selected_config = config;

            // Enable MOSFET group of newly selected config
            enable_mosfet_group(&config_manager->selected_config->mosfet_group);

            config_selected = true;
            break;
        }
    }

    return config_selected;
}