//
// Created by paulo on 02/05/2023.
//

#include "menu_nav.h"

/**
 * @brief Configura o novo estado do menu após um evento de press.
 *
 * @param[in,out] navigator Referência para o navegador atual.
 */
static void handle_press(navigator_t* navigator, eqm_settings_t* settings) {

    switch (navigator->current_screen->details.type) {
        case MONITOR_SCREEN:
        case SETTING_SCREEN:
            navigator->current_screen = navigator->screens[navigator->current_screen->next_screens[0]];
            break;
        case OPTIONS_SCREEN:
            navigator->current_screen = navigator->screens[navigator->current_screen->next_screens[navigator->ctrl.menu.selection]];
            break;
        case CONFIRM_SCREEN:
            if (navigator->ctrl.confirm.is_confirmed) {
                navigator->current_screen->confirm_callback(true, navigator->ctrl.confirm.previous_screen_selection,
                                                            settings);
            }
            navigator->current_screen = navigator->screens[navigator->current_screen->next_screens[navigator->ctrl.confirm.is_confirmed]];
            break;
        default:
            break;
    }

    switch (navigator->current_screen->details.type) {
        case MONITOR_SCREEN:
            navigator->ctrl.monitor.update_threshold = 100;
            navigator->ctrl.monitor.update_counter = 0;
            break;
        case OPTIONS_SCREEN:
            navigator->ctrl.menu.head = 0;
            navigator->ctrl.menu.selection = 0;
            break;
        case CONFIRM_SCREEN:
            navigator->ctrl.confirm.previous_screen_selection = navigator->ctrl.menu.selection;
            navigator->ctrl.confirm.is_confirmed = false;
            break;
        default:
            break;
    }

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
    uint8_t prev_sel = navigator->ctrl.menu.selection;
    int16_t new_selection = (int16_t) (prev_sel + direction);

    /** Clamp para os limites do menu. */
    if (new_selection < 0) {
        new_selection = 0;
    } else if (new_selection == navigator->current_screen->details.content_amount) {
        new_selection = (int16_t) (navigator->current_screen->details.content_amount - 1);
    }

    /** Movimenta a cabeça do menu quando necessário. */
    if ((navigator->ctrl.menu.head) && (new_selection < navigator->ctrl.menu.head)) {
        navigator->ctrl.menu.head--;
    } else if (new_selection == navigator->ctrl.menu.head + MENU_ROWS) {
        navigator->ctrl.menu.head++;
    }

    /** Pula as ocorrências não visíveis. */
    for (; !navigator->current_screen->contents[new_selection].opt.is_visible; (direction > 0) ? new_selection++
                                                                                               : new_selection--) {

        if (new_selection == (direction > 0 ? navigator->current_screen->details.content_amount : 0)) {
            new_selection = prev_sel;
            break;
        }
    }

    navigator->ctrl.menu.selection = (uint8_t) new_selection;
}

static void update_confirm(navigator_t* navigator, eqm_settings_t* settings, int8_t direction) {
    if (navigator->current_screen->confirm_callback == NULL) {
        return;
    }

    navigator->ctrl.confirm.is_confirmed = direction > 0;
    navigator->current_screen->confirm_callback(false, direction, settings);
}

static void handle_rotation(navigator_t* navigator, eqm_settings_t* settings, int8_t direction) {
    switch (navigator->current_screen->details.type) {
        case SETTING_SCREEN:
            update_setting(navigator, settings, direction);
            break;
        case OPTIONS_SCREEN:
            update_selection(navigator, direction);
            break;
        case CONFIRM_SCREEN:
            update_confirm(navigator, settings, direction);
            break;
        default:
            break;
    }
    navigator->has_changes = true;
}

void handle_rotary_event(navigator_t* navigator, eqm_settings_t* settings) {
    if (rotary_pop_press()) {
        handle_press(navigator, settings);
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