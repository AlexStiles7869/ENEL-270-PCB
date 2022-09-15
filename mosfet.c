//
// Created by Alexander Stiles on 15/09/22.
//
//
//
//

#include "mosfet.h"

/** MOSFET */

/**
 * Enable a mosfet
 * @param mosfet mosfet to be enabled
 */
static void enable_mosfet(mosfet_t* mosfet) {
    // GPIO management to enable specific mosfet

    // Update struct
    mosfet->on = true;
}

/**
 * Disable a mosfet
 * @param mosfet mosfet to be disabled
 */
static void disable_mosfet(mosfet_t* mosfet) {
    // GPIO management to disable specific mosfet

    // Update struct
    mosfet->on = false;
}

/** MOSFET GROUP */

/**
 * Create a base mosfet group
 * @return A blank mosfet group
 */
mosfet_group_t create_mosfet_group() {
    mosfet_group_t mosfet_group = {
            .enabled = false,
            .num_mosfets = 0,
    };

    return mosfet_group;
}

/**
 * Helper function for me to add mosfets to the predefined groups
 *
 * @param mosfet_group The mosfet group to add the mosfet to
 * @param mosfet The mosfet to add
 * @return Whether the mosfet was successfully added
 */
bool add_mosfet(mosfet_group_t* mosfet_group, mosfet_t mosfet) {
    bool mosfet_added = false;

    if ((mosfet_group->num_mosfets + 1) < MAX_GROUP_MOSFETS) {
        // Add the mosfet to the group and increment number of mosfets in group
        mosfet_group->group_mosfets[mosfet_group->num_mosfets++] = mosfet;

        // Set flag
        mosfet_added = true;
    }

    return mosfet_added;
}

/**
 * Enable all the mosfets in a group
 * @param mosfet_group Group to be enabled
 */
void enable_mosfet_group(mosfet_group_t* mosfet_group) {

    // NOTE: Add check that no other config is on

    // If the group is already enabled, return early as no work to be done.
    if (mosfet_group->enabled) {
        return;
    }

    for (uint8_t i = 0; i < mosfet_group->num_mosfets; i++) {
        enable_mosfet(&mosfet_group->group_mosfets[i]);
    }

    mosfet_group->enabled = true;
}

/**
 * Disable all mosfets in a group
 * @param mosfet_group Group to be disabled
 */
void disable_mosfet_group(mosfet_group_t* mosfet_group) {
    // If the group is not enabled, return early as no other work to be done.
    if (!mosfet_group->enabled) {
        return;
    }

    for (uint8_t i = 0; i < mosfet_group->num_mosfets; i++) {
        disable_mosfet(&mosfet_group->group_mosfets[i]);
    }

    mosfet_group->enabled = false;
}
