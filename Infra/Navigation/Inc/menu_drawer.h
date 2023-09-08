/**
 * @file menu_drawer.h
 * @author Paulo Santos (pauloxrms@gmail.com)
 * @brief //TODO
 * @version 0.1
 * @date 23-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DEBUG_MENU_DRAWER_H
#define DEBUG_MENU_DRAWER_H

#include "menu_infra.h"
#include "menu_nav.h"
#include "bitmaps.h"

#define X_LEFT_PAD 15
#define Y_ROW_PAD 11
#define Y_BY_ENUM(enum_val) (((enum_val) * (Y_ROW_PAD)) + 2)

/**
 * @brief Desenha a tela atual no display.
 *
 * @param[in] navigator Referencia do navegador responsável pela lógica do menu.
 * @param[in] settings Referencia do property board da EQM.
 */
void update_screen(navigator_t* navigator, eqm_settings_t const* settings);

#endif//DEBUG_MENU_DRAWER_H