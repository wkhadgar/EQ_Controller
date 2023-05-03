//
// Created by paulo on 02/05/2023.
//

#include "menu_nav.h"

void handle_press(navigator_t* navigator) {
    switch (navigator->current_screen->details.type) {
        case MONITOR_SCREEN:
        case SETTING_SCREEN:
            navigator->current_screen = navigator->screen_table[navigator->screen_flow[0]];
            update_screen_targets(navigator);
            break;
        case MENU_SCREEN:
            navigator->current_screen = navigator->screen_table[navigator->screen_flow[navigator->ctrl.menu.selection]];
            update_screen_targets(navigator);
            if (navigator->current_screen->details.type == SETTING_SCREEN) {
                update_setting(navigator);
            }
            break;
    }
}

void update_setting(navigator_t* navigator) {
    navigator->ctrl.setting_handler = navigator->handler_table[navigator->current_screen->details.id];
}

void update_selection(navigator_t* navigator, int8_t direction) {
    int16_t new_selection = (int16_t) (navigator->ctrl.menu.selection + direction);

    if (new_selection < 0) {
        new_selection = 0;
    } else if ((navigator->ctrl.menu.head) && (new_selection < navigator->ctrl.menu.head)) {
        navigator->ctrl.menu.head--;
    } else if (new_selection == navigator->ctrl.menu.head + MENU_ROWS) {
        navigator->ctrl.menu.head++;
    } else if (new_selection == navigator->current_screen->details.content_amount) {
        new_selection = (int16_t) (navigator->current_screen->details.content_amount - 1);
    }

    navigator->ctrl.menu.selection = (uint8_t) new_selection;
}

void update_content(navigator_t* navigator, uint8_t index, uint8_t* data) {
    navigator->current_screen->contents[index].data = data;
}