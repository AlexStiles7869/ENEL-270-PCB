
#include "config.h"
#include "mosfet.h"

#include <stdio.h>
#include <stdlib.h>

void print_config_manager(config_manager_t* config_manager) {
    printf("CONFIG MANAGER DETAILS: \n");
    printf("Number of Configs: %d\n\n", config_manager->num_configs);

    // Iterate over all the configs and print their data
    for (int i = 0; i < config_manager->num_configs; i++) {
        config_t* config = &config_manager->configs[i];

        printf("Config %d Details:\n", config->id);
        printf("ID: %d | Name: %s | Selected: %d | Num Mosfets: %d\n",
               config->id, config->config_name, config->selected, config->mosfet_group.num_mosfets);
        printf("MOSFETs:\n", config->id);

        for (int j = 0; j < config->mosfet_group.num_mosfets; j++) {
                printf("MOSFET pin: %d | MOSFET on: %d\n", config->mosfet_group.group_mosfets[j].GPIO_pin, config->mosfet_group.group_mosfets[i].on);
        }

        printf("\n");
    }

    printf("Selected Config Name: %s\n", config_manager->selected_config != NULL ? config_manager->selected_config->config_name : "None");
}

void test_mosfet_groups() {
    mosfet_t mosfets[100];
    mosfet_group_t mosfet_groups[10];

    int i;
    int j;

    for (i = 0; i < 10; i++) {

        mosfet_groups[i] = create_mosfet_group();

        for (j = 0; j < 10; j++) {
            mosfets[(i * 10) + j].on = j % 2;
            mosfets[(i * 10) + j].GPIO_pin = (i * 10) + j;

            add_mosfet(&mosfet_groups[i], mosfets[(i * 10) + j]);
        }
    }

    for (i = 0; i < 10; i++) {
        printf("MOSFET Group %d: Num MOSFETS %d | Enabled %d\n", i, mosfet_groups[i].num_mosfets, mosfet_groups[i].enabled);
        for (j = 0; j < 10; j++) {
            printf("On: %d | Pin: %d\n", mosfet_groups[i].group_mosfets[j].on, mosfet_groups[i].group_mosfets[j].GPIO_pin);

        }
    }
}

void test_config_management() {
    config_manager_t config_manager = create_config_manager();

    mosfet_t mosfet_1 = {.GPIO_pin = 5, .on = false};
    mosfet_t mosfet_2 = {.GPIO_pin = 6, .on = false};
    mosfet_group_t mosfet_group_1 = create_mosfet_group();
    add_mosfet(&mosfet_group_1, mosfet_1);
    add_mosfet(&mosfet_group_1, mosfet_2);
    config_t config_1 = create_config("Diff Amp", mosfet_group_1);

    mosfet_t mosfet_3 = {.GPIO_pin = 7, .on = false};
    mosfet_t mosfet_4 = {.GPIO_pin = 9, .on = false};
    mosfet_group_t mosfet_group_2 = create_mosfet_group();
    add_mosfet(&mosfet_group_2, mosfet_3);
    add_mosfet(&mosfet_group_2, mosfet_4);
    config_t config_2 = create_config("Buffer", mosfet_group_2);

    add_config(&config_manager, config_1);
    add_config(&config_manager, config_2);

    select_config_by_ID(&config_manager, 0);
    print_config_manager(&config_manager);
    select_config_by_ID(&config_manager, 1);
    print_config_manager(&config_manager);
}

int main() {
    test_config_management();

    return EXIT_SUCCESS;
}
