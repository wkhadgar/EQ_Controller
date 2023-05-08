//
// Created by paulo on 02/05/2023.
//

#ifndef EQ_CONTROLLER_MENU_NAV_H
#define EQ_CONTROLLER_MENU_NAV_H

#include "menu_infra.h"
#include "rotary_events.h"

#define MENU_ROWS 6


/**
 * @brief Processa eventos do rotary encoder.
 *
 * @param[in,out] navigator_w Referência para o wrapper atual.
 */
void handle_rotary_event(navigator_t* navigator, eqm_settings_t* settings);

/**
 * @brief Configura um fluxo de navegação.
 *
 * @param[in,out] navigator_w Referência para o wrapper atual.
 */
inline void update_screen_targets(navigator_t* navigator) {
    navigator->next_screens = navigator->screen_flow[navigator->current_screen->details.id].flow;
}

#endif//EQ_CONTROLLER_MENU_NAV_H