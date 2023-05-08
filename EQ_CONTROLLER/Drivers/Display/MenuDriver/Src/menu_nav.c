//
// Created by paulo on 02/05/2023.
//

#include "menu_nav.h"

/**
 * @brief Configura o novo estado do menu após um evento de press.
 *
 * @param[in,out] navigator Referência para o navegador atual.
 */
static void handle_press(navigator_t* navigator) {
    switch (navigator->current_screen->details.type) {
        case MONITOR_SCREEN:
        case SETTING_SCREEN:
            navigator->current_screen = navigator->screen_flow[navigator->next_screens[0]].screen;
            break;
        case OPTIONS_SCREEN:
            navigator->current_screen = navigator->screen_flow[navigator->next_screens[navigator->ctrl.menu.selection]].screen;
            break;
    }

    switch (navigator->current_screen->details.type) {
        case MONITOR_SCREEN:
            navigator->ctrl.monitor.update_threshold = 100;
            navigator->ctrl.monitor.update_counter = 100;
            break;
        case SETTING_SCREEN:
            break;
        case OPTIONS_SCREEN:
            navigator->ctrl.menu.head = 0;
            navigator->ctrl.menu.selection = 0;
            break;
        default:
            break;
    }

    update_screen_targets(navigator);
    navigator->has_changes = true;
}

/**
 * @brief Altera a configuração atual de acordo com a direção indicada.
 *
 * @param[in,out] navigator_w Referência para o wrapper atual.
 * @param direction Direção da navegação.
 */
static void update_setting(navigator_t const* navigator, eqm_settings_t* settings, int8_t direction) {
    if (navigator->current_screen->setting_callback == NULL) {
        return;
    }

    if (direction > 0) {
        direction *= 5;
    }

    navigator->current_screen->setting_callback(direction, settings);
}

/**
 * @brief Navega no menu de acordo com a direção indicada.
 *
 * @param[in,out] navigator_w Referência para o wrapper atual.
 * @param direction Direção da navegação.
 */
static void update_selection(navigator_t* navigator, int8_t direction) {
    int16_t new_selection = (int16_t) (navigator->ctrl.menu.selection + direction);

    if (new_selection < 0) {
        new_selection = 0;
    } else if (new_selection == navigator->current_screen->details.content_amount) {
        new_selection = (int16_t) (navigator->current_screen->details.content_amount - 1);
    }

    if ((navigator->ctrl.menu.head) && (new_selection < navigator->ctrl.menu.head)) {
        navigator->ctrl.menu.head--;
    } else if (new_selection == navigator->ctrl.menu.head + MENU_ROWS) {
        navigator->ctrl.menu.head++;
    }


    navigator->ctrl.menu.selection = (uint8_t) new_selection;
}

static void handle_rotation(navigator_t* navigator, eqm_settings_t* settings, int8_t direction) {
    switch (navigator->current_screen->details.type) {
        case SETTING_SCREEN:
            update_setting(navigator, settings, direction);
            break;
        case OPTIONS_SCREEN:
            update_selection(navigator, direction);
            break;
        default:
            break;
    }
    navigator->has_changes = true;
}

void handle_rotary_event(navigator_t* navigator, eqm_settings_t* settings) {
    if (rotary_pop_press()) {
        handle_press(navigator);
    } else {
        switch (rotary_pop_dir()) {
            case CW:
                handle_rotation(navigator, settings, 1);
                break;
            case CCW:
                handle_rotation(navigator, settings, -1);
                break;
            default:
                break;
        }
    }
}