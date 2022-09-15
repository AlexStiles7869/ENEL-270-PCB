//
// Created by Alexander Stiles on 15/09/22.
//

#ifndef SOFTWARE_MOSFET_H
#define SOFTWARE_MOSFET_H

#include <stdint.h>
#include <stdbool.h>

/**
 * The maximum number of mosfets a group can have
 */
#define MAX_GROUP_MOSFETS 16

typedef struct {
    bool on;
    uint8_t GPIO_pin;
} mosfet_t;

typedef struct {
    bool enabled; // Whether the group is enabled
    mosfet_t group_mosfets[MAX_GROUP_MOSFETS]; // Array of group mosfets
    uint8_t num_mosfets; // Number of mosfets in the group
} mosfet_group_t;

mosfet_group_t create_mosfet_group();
bool add_mosfet(mosfet_group_t* mosfet_group, mosfet_t mosfet);
void enable_mosfet_group(mosfet_group_t* mosfet_group);
void disable_mosfet_group(mosfet_group_t* mosfet_group);

#endif //SOFTWARE_MOSFET_H
