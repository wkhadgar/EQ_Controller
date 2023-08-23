/**
 * @file menu_nav.h
 * @author Paulo Santos (pauloxrms@gmail.com)
 * @brief //TODO
 * @version 0.1
 * @date 23-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

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

#endif//EQ_CONTROLLER_MENU_NAV_H